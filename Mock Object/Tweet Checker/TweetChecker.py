import os
import twitter #pip install python-twitter


URL = "https://twitter.com/CoderOnStyle"


def tweet(api, message):
    if len(message) > 280:
        message = message.strip(",.?!/")
    if len(message) > 280:
        message = message.replace('ck', 'x')
        message = message.replace('ex', 'x')
    if len(message) > 280:
        message = message.replace('and', '&')
    if len(message) > 280:
        message = "The message could not be published. {}".format(URL)
    status = api.PostUpdate(message)
    return status

def main():
    api = twitter.api(consumer_key=os.getenv('CONSUMER_KEY'),
                      consumer_secret=os.getenv('CONSUMER_SECRET'),
                      access_token_key=os.getenv('ACCESS_TOKEN_KEY'),
                      access_token_secret=os.getenv('ACCESS_TOKEN_SECRET'))
    msg = raw_input("What do you want to tweet? :")
    tweet(api, msg)


if __name__ == '__main__':
    main()
