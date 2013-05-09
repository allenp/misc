import sys
import json
import operator


def main():
    hashtags = {}
    with open(sys.argv[1], "r") as tweet_file:
        for line in tweet_file:
            tweet = json.loads(line)
            if "entities" in tweet:
                for hashtag in (
                    hashtag["text"]
                        for hashtag in tweet["entities"]["hashtags"]
                ):
                    if hashtag in hashtags:
                        hashtags[hashtag] += 1.0
                    else:
                        hashtags[hashtag] = 1.0

    sorted_hash = sorted(hashtags, key=lambda x: hashtags[x], reverse=True)
    sorted_hash = sorted_hash[:min(10, len(sorted_hash))]

    for key in sorted_hash:
        print key.encode('utf-8'), hashtags[key]

if __name__ == "__main__":
    main()
