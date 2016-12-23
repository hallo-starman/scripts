#!/usr/bin/env python3

from selenium import webdriver
from selenium.webdriver.support.ui import WebDriverWait
import smtplib
from email.mime.multipart import MIMEMultipart
from email.mime.text import MIMEText

def getLink():
	# open up Firefox and navigate to website
	page = webdriver.Firefox()
	page.get('https://brainpickings.org')

	prevUrl = page.current_url
	# try clicking the 'surprise me' link
	# if that link doesn't load, then refresh and try again
	try:
		page.find_element_by_link_text('surprise me').click()
	except:
		page.refresh()
		page.find_element_by_link_text('surprise me').click()
	
	# make sure that the page loads fully to get the url of the new website
	while page.current_url == prevUrl:
		WebDriverWait(page, 10)
	
	# print out the link of the article 
	theLink = page.current_url
	page.quit()
	return theLink

def sendMail(theArticle):
    # the address to send from and the destination address
	fromAddr = '****@blah.com'
	toAddr = '******@blahblah.com'
	# create message object
	msg = MIMEMultipart()
	# fill out all info
	msg['From'] = fromAddr
	msg['To'] = toAddr
	msg['Subject'] = 'Daily Article'
	# body of message -- the random link
	msg.attach(MIMEText(theArticle, 'plain'))

	# connect with gmail's smtp server
	server = smtplib.SMTP('smtp.gmail.com', 587)
	server.starttls()
	# log in to the account mail is being sent from
	server.login(fromAddr, password)

	text = msg.as_string()
	# send the message
	server.sendmail(fromAddr, toAddr, text)
	server.quit()	
	
link = getLink()
sendMail(link)
