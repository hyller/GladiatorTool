import requests

url = "http://127.0.0.1:4001/zigbee_simulation/first/network/init"

payload="{\r\n    \"resume\": true\r\n}"
headers = {
  'Content-Type': 'application/json'
}

response = requests.request("POST", url, headers=headers, data=payload)

print(response.text)
