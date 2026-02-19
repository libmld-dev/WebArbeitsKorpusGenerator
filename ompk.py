#!/bin/python3
import sqlite3
import sys
import os

# connect to db
conn = sqlite3.connect("million_post_corpus/corpus.sqlite3")
cursor = conn.cursor()

# fetch data
topicl = sys.argv[1] + "/%"
topicm = "%/" + sys.argv[1] + "/%"
topicr = "%/" + sys.argv[1]
cursor.execute("SELECT * FROM Articles WHERE Path LIKE ? OR Path LIKE ? OR PATH LIKE ?;", (topicl, topicm, topicr))
result = cursor.fetchall()

# iter results
cnt = 0
for entry in result:
    # print status
    print("Processing ", cnt, " of ", len(result))

    # print metadata
    foutMeta = open("meta.txt", "w+")
    print("\"" + str(entry[0]) + "\",\"" + str(entry[1]) + "\",\"" + str(entry[2]) + "\",\"" + str(entry[3]) + "\"", file=foutMeta)
    foutMeta.flush()
    foutMeta.close()

    # filter each article separatly by trafilatura...
    # its slow, but otherwise trafilatura misses a lot of content
    ftmp = open("tmp", "w+")
    ftmp.write(entry[4])
    ftmp.flush()
    os.system("cat tmp | trafilatura --no-tables > article.txt")
    ftmp.close()
    os.system("rm tmp")

    # run the remaining steps
    os.system("./preanna article.txt web_split.txt")
    os.system("./bin/tree-tagger -lemma -token ./lib/german.par ./web_split.txt ./korp.txt")
    os.system("./anna korp.txt korp.csv")
    os.system("./postanna korp.csv korpm.csv meta.txt 0")
    os.system("./clean.sh && rm article.txt")

    cnt = cnt + 1

# print and cleanup
print(cnt, " Treffer!")
