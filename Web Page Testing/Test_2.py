from selenium import webdriver
import unittest
from selenium.webdriver.common.keys import Keys
import time


class WikipediaSearch(unittest.TestCase):


    def setUp(self):
        self.driver = webdriver.Chrome('/Users/elizabethlorelei/Downloads/chromedriver')

    def test_1(self):
        self.driver.get('https://www.wikipedia.org/')
        time.sleep(2)
        input_field = self.driver.find_element_by_id('searchInput')
        input_field.send_keys('America')
        input_field.send_keys(Keys.DOWN)
        time.sleep(2)
        input_field.send_keys(Keys.ENTER)

        time.sleep(2)


    
    '''def test_2(self):

        input_field_1 = self.driver.find_elements_by_class_name('dablink hatnote noprint')
        input_field_1[0].send_keys(Keys.ENTER)
    '''


    def tearDown(self):
        self.driver.quit()


if __name__ == '__main__':
    unittest.main()
