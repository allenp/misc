import sys
import json
import string

def tweet_tokens(text):
    '''
    computes the frequence of each word within a single tweet
    '''
    exclude = set(string.punctuation)
    tokens = {}
    for word in (w for w in text.split()):
        #word = ''.join(ch for ch in word if ch not in exclude).strip()
        word = word.strip()
        if len(word) > 0 and not is_numeric(word):
            if word in tokens:
                tokens[word] += 1
            else:
                tokens[word] = 1

    return tokens


def is_numeric(word):
    try:
        float(word)
        return True
    except ValueError:
        return False


def main():
    '''
    loads tweets file, parses, and aggregates word
    frequency. prints to stdout
    '''
    freq = {}
    with open(sys.argv[1], "r") as tweet_file:
        for line in tweet_file:
            tweet = json.loads(line)
            if "text" in tweet:
                tokens = tweet_tokens(tweet["text"].encode('utf-8'))
                for word in tokens:
                    if word in freq:
                        freq[word] = freq[word] + tokens[word]
                    else:
                        freq[word] = tokens[word]

    total = sum(freq.values())

    for word in freq:
        freq[word] = float(freq[word] * 1.0 / total)
        print "%s %.8f" % (word, freq[word])

if __name__ == "__main__":
    main()
