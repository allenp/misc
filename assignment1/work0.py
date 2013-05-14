import urllib
import json

def main():

    for i in range(1,3):
        response = urllib.urlopen("http://search.twitter.com/search.json?q=acmatic&page=%d" % i)
        result = json.load(response)["results"]

        for tweet in result:
            print tweet["text"].encode('utf-8') + "\n"


if __name__ == "__main__":
    main()
