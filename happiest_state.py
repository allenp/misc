import sys
import json
import string


def tweet_score(tweet, sent_file):
    '''
    Calculates the sum of all recognized words in a tweet
    '''
    score = 0
    for word in tweet.split():
        score += word_sentiment(word, sent_file)

    return score


def word_sentiment(word, sent_file):
    '''
    Check current <word> against the sentiment file
    and return sentiment score if found other wise return 0
    '''
    sent_file.seek(0)
    sent = 0
    exclude = set(string.punctuation)
    word = ''.join(ch for ch in word if ch not in exclude)
    word = word.lower().strip()

    for line in sent_file:
        (clean, score) = line.split('\t')
        clean = clean.lower().strip()
        if word == clean:
            sent = score
            break

    return float(sent)


def get_us_state(tweet):
    '''
    Check tweets for location data indicating the city.
    if no location data is found, return false
    '''
    if "place" in tweet and tweet["place"] is not None and tweet["place"]["country_code"] == "US":
        return get_loc_from_place(tweet["place"])
    #elif "user" in tweet and "location" in tweet["user"]:
    #    return get_loc_from_str(tweet["user"]["location"])
    #elif "coordinates" in tweet:
    #    return get_loc_from_coords(tweet["coordinates"])
    else:
        return False


def get_loc_from_place(place):
    if "full_name" in place:
        return get_loc_from_str(place["full_name"])


def get_loc_from_str(user_loc):
    if user_loc is None:
        return False
    location = user_loc.split(",")
    if len(location) > 1:
        return location[1].strip()
    else:
        return location[0].strip()


def get_loc_from_coords(coords):
    return False


def main():
    '''
    Read in sentiment file and tweet files
    Then calculate and print the sentiment score
    for each tweet to stdout
    '''
    sent_file = open(sys.argv[1], "r")
    states = {}

    with open(sys.argv[2], "r") as tweet_file:
        for line in tweet_file:
            tweet = json.loads(line)
            if "text" in tweet:
                state = get_us_state(tweet)
                if state is not False:
                    score = tweet_score(
                        tweet["text"].encode('utf-8'),
                        sent_file
                    )
                    s = state.encode('utf-8')
                    if s in states:
                        states[s] += score
                    else:
                        states[s] = score

    sorted_states = sorted(states, key=lambda x: states[x], reverse=True)

    print sorted_states[0]

    #for e in states:
        #print "%s %.2f" % (e, states[e])

    if not tweet_file.closed:
        tweet_file.close()
    if not sent_file.closed:
        sent_file.close()

if __name__ == '__main__':
    main()
