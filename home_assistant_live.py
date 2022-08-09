import time
import webbrowser
import pyautogui
from requests import get

counter =0

while 1 :
    try:
        url = "http://10.20.0.230:8123/api/"
        headers = {
            "Authorization": "Bearer eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJjMTZlNzMzZDExZmI0NDk3YTRmNDc5YmQ0YmE3YjVmMSIsImlhdCI6MTY1OTY4NDMxOSwiZXhwIjoxOTc1MDQ0MzE5fQ.1uMC30pUbZjhrJwVyoCgkn-05pJB1dvVUFo4KpzKqCE",
            "content-type": "application/json",
        }
        response = get(url, headers=headers)
        if str(response.text) == '{"message":"API running."}':
            print(response.text)
            counter+=1
    except :
        pass
    if counter >= 1 :
        webbrowser.open("http://10.20.0.230:8123/lovelace/0?kiosk")
        pyautogui.press('f11')
        quit()
    time.sleep(2)
