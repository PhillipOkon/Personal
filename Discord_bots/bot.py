# bot.py  created to Scrape a Dynamic table off a URL then send it to a discord channel
import os
import discord 
import asyncio
import pandas as pd
from discord.ext import tasks
from dotenv import load_dotenv
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.options import Options

#Method opening Chrome broswer using selenium then saving table data to a dataframe 
def get_data(url):
    #Makes openning chrome --headless i.e no browser popup
    options = Options()
    options.add_argument('--headless=new')
    options.add_argument('--no-sandbox')
    options.add_argument('--disable-dev-shm-usage')

    driver = webdriver.Chrome(options=options)
    driver.get(url)

    #waits 10 secs so the page fully loads
    driver.implicitly_wait(5)

    #Saves website as a html and decodes it
    html = driver.page_source
    html_dec = html.encode('utf-8').decode('ascii', 'ignore')
    soup = BeautifulSoup(html_dec, "html.parser")

    #creates empty list
    data = []

    #saves all table data under <a> with class label code
    codes = soup.find_all('a', class_='label-code')

    #iterator loop for getting only href then converting into strings then appending into list
    for code in codes:
        link = code.get('href')
        slink = str(link)
        data.append(slink)

    #exits driver
    driver.quit()

    #returns data list
    return data

#func for connecting to discord
def update(data):
    load_dotenv()
    #secret token for bot
    TOKEN = os.getenv('DISCORD_TOKEN')

    client = discord.Client(intents=discord.Intents.all()) 

    #on load, it checks if bot is online then starts main msg loop
    @client.event
    async def on_ready():
        print("Logged in as {0.user}".format(client))
        await client.change_presence(status=discord.Status.online)
        msg.start()

    #in case a user wants to manually update the data
    @client.event
    async def on_message(message):
        if message.author == client.user:
            return
        
        if message.content.startswith('$update'):
            await message.channel.send("Manually updating.... \n")
            await message.channel.send(data)

    #main loop, on a 24 hour cycle, it ways 5 secs for all data then sends message to specified channel
    @tasks.loop(hours=24)
    async def msg():
            await asyncio.sleep(5)
            channel = client.get_channel(1127370585236832357)
            await channel.send("Hey guys here are all viable codes: \n")
            await channel.send(data)
        
    client.run(TOKEN)
    
def main():
    data = get_data("https://swq.jp/l/en-US/index.html")
    update(data)


if __name__ == '__main__':
    main()
