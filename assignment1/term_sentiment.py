import sys
import json
import string


def tweet_score(tweet, sent_file):
    '''
    Calculates the sum of all recognized words in a tweet
    '''
    score = 0
    words = []
    scores = {}
    for word in tweet.split():
        if not is_numeric(word):
            result = word_sentiment(word, sent_file)
            if result is False:
                words.append(word)
            else:
                score += float(result)

    scores = ((w, score) for w in words)

    return scores


def is_numeric(word):
    try:
        float(word)
        return True
    except ValueError:
        return False


def word_sentiment(word, sent_file):
    '''
    Check current <word> against the sentiment file
    and return sentiment score if found other wise return 0
    '''
    #if sent_file is not None and not sent_file.closed:
    sent_file.seek(0)

    sent = 0
    exclude = set(string.punctuation)
    word = ''.join(ch for ch in word if ch not in exclude)
    word = word.lower().strip()
    found = False

    for line in sent_file:
        (clean, score) = line.split('\t')
        clean = clean.lower().strip()
        if word == clean:
            sent = score
            found = True
            break

    if found:
        return float(sent)
    else:
        return False


def main():
    '''
    Read in sentiment file and tweet files
    Then calculate and print the sentiment score
    for each tweet to stdout
    '''
    sent_file = open(sys.argv[1], "r")

    new_words = {}
    with open(sys.argv[2], "r") as tweet_file:
        for line in tweet_file:
            tweet = json.loads(line)
            if "text" in tweet:
                scores = tweet_score(
                    tweet["text"].encode('utf-8'),
                    sent_file
                )
                for t in scores:
                    if t[0] in new_words:
                        new_words[t[0]] = (new_words[t[0]] + t[1]) / 2
                    else:
                        new_words[t[0]] = t[1]

    for word in new_words:
        print "%s %.2f" % (word, new_words[word])

    if not tweet_file.closed:
        tweet_file.close()
    if not sent_file.closed:
        sent_file.close()

if __name__ == '__main__':
    main()
