import sys
import json


def tweet_score(tweet, sent_file):
    '''
    Calculates the sum of all recognized words in a tweet
    '''
    score = 0
    for word in tweet.split(' '):
        score += word_sentiment(word, sent_file)

    return score


def word_sentiment(word, sent_file):
    '''
    Check current <word> against the sentiment file
    and return sentiment score if found other wise return 0
    '''
    if sent_file is not None and not sent_file.closed:
        sent_file.seek(0)

    sent = 0
    for line in sent_file:
        if word.lower() in line.lower():
            sent = line.split('\t')[1]
            break

    return float(sent)


def main():
    '''
    Read in sentiment file and tweet files
    Then calculate and print the sentiment score
    for each tweet to stdout
    '''
    sent_file = open(sys.argv[1], "r")

    with open(sys.argv[2], "r") as tweet_file:
        for line in tweet_file:
            tweet = json.loads(line)
            if "text" in tweet:
                score = tweet_score(tweet["text"].encode('utf-8'), sent_file)
                print str(score)

    if not tweet_file.closed:
        tweet_file.close()
    if not sent_file.closed:
        sent_file.close()

if __name__ == '__main__':
    main()
