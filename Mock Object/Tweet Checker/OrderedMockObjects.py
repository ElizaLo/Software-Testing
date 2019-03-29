import unittest
import pytest
from mock import Mock


import TweetChecker


class TweetTest(unittest.TestCase):
    @pytest.mark.run('first')
    def test_1(self):
        mock_twitter = Mock()
        TweetChecker.tweet(mock_twitter, "message")
        mock_twitter.PostUpdate.assert_called_with("message")

    @pytest.mark.run('second_to_last')
    def test_3(self):
        mock_twitter = Mock()
        TweetChecker.tweet(mock_twitter, "Say hello")
        mock_twitter.PostUpdate.assert_called_with("Say helo")

    @pytest.mark.run('second')
    def test_2(self):
        mock_twitter = Mock()
        TweetChecker.tweet(mock_twitter, "“Can’t repeat the past?…Why of course you can!” ― F. Scott Fitzgerald, The Great Gatsby")
        mock_twitter.PostUpdate.assert_called_with("“Can’t repeat the past?…Why of course you can!” ― F. Scott Fitzgerald, The Great Gatsby")


    @pytest.mark.run('last')
    def test_4(self):
        mock_twitter = Mock()
        TweetChecker.tweet(mock_twitter, "Hello, it's me")
        mock_twitter.PostUpdate.assert_called_with("Hello, it's me")

'''
    def test_3(self):
        mock_twitter = Mock()
        TweetChecker.tweet(mock_twitter, "He smiled understandingly-much more than understandingly. It was one of those rare smiles with a quality of eternal reassurance in it, that you may come across four or five times in life. It faced--or seemed to face--the whole eternal world for an instant, and then concentrated on you with an irresistible prejudice in your favor. It understood you just as far as you wanted to be understood, believed in you as you would like to believe in yourself, and assured you that it had precisely the impression of you that, at your best, you hoped to convey. ― F. Scott Fitzgerald, The Great Gatsby")
        mock_twitter.PostUpdate.assert_called_with("He smiled understandingly-much more than understandingly. It was one of those rare smiles with a quality of eternal reassurance in it, that you may come across four or five times in life. It faced--or seemed to face--the whole eternal world for an instant, and then concentrated on you with an irresistible prejudice in your favor. It understood you just as far as you wanted to be understood, believed in you as you would like to believe in yourself, and assured you that it had precisely the impression of you that, at your best, you hoped to convey. ― F. Scott Fitzgerald, The Great Gatsby")

    def test_4(self):
        mock_twitter = Mock()
        TweetChecker.tweet(mock_twitter, "“He looked at her the way all women want to be looked at by a man.” ― F. Scott Fitzgerald, The Great Gatsby")
        mock_twitter.PostUpdate.assert_called_with("message")

'''


if __name__ == '__main__':
    unittest.main()
