from selenium import webdriver
import unittest
from selenium.webdriver.common.keys import Keys
import time


driver = webdriver.Chrome('/Users/elizabethlorelei/Downloads/chromedriver')

driver.get('https://www.sephora.com')
time.sleep(2)
input_field_1 = driver.find_element_by_class_name('css-zea1jq')
input_field_1.send_keys(Keys.ENTER)
time.sleep(2)

input_field_2 = driver.find_element_by_id('site_search_input')
input_field_2.send_keys('Lancome')
time.sleep(1)
input_field_2.send_keys(Keys.ENTER)
time.sleep(2)
