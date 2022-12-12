USEROVERRIDE=0
SENSORDATA=0
VENUE='VASCO DA GAMA'

favourable=['Sunny','Partly cloudy']

import requests
from flask import Flask

from flask import request
from flask import jsonify

app = Flask(__name__)

@app.route("/auto")
def auto():
    global USEROVERRIDE
    USEROVERRIDE=2
    print(USEROVERRIDE)
    return 'success'

@app.route("/get/auto")
def get_auto():
    global USEROVERRIDE
    print(USEROVERRIDE)
    return str(USEROVERRIDE)
  
@app.route("/")
def home():
    return "There's nothing here"

@app.route("/get/user")
def get_user():
  global USEROVERRIDE
  print(USEROVERRIDE)
  return str(USEROVERRIDE)

@app.route("/set/user/1")
def set_user1():
  global USEROVERRIDE
  USEROVERRIDE=1
  return str(USEROVERRIDE)

@app.route("/set/user/0")
def set_user0():
  global USEROVERRIDE
  USEROVERRIDE=0
  return str(USEROVERRIDE)

@app.route("/get/sensor")
def set_sensor():
  global SENSORDATA
  return str(SENSORDATA)

@app.route("/set/sensor/1")
def set_sensor1():
  global SENSORDATA
  SENSORDATA=1
  return str(SENSORDATA)

@app.route("/set/sensor/0")
def set_sensor0():
  global SENSORDATA
  SENSORDATA=0
  return str(SENSORDATA)



@app.route('/set/venue',methods=['Post'])
def set_whether():
  res=request.get_json()
  VENUE=res['data']
  return 'Success'





@app.route("/get/command")
def command():
  res=requests.get('http://api.weatherapi.com/v1/current.json?key=68d29185eac8486a857175637220712&q=VASCO DA GAMA&aqi=no')
  data=res.json()
  print(data['location']['name'])
  print(data['current']['condition']['text'])
  value=data['current']['condition']['text']
  day=data['current']['is_day']
  if USEROVERRIDE==0:
    return str(0)
  elif USEROVERRIDE==1:
    return  str(1)
  elif USEROVERRIDE==2:
    if SENSORDATA==1:
      return str(0)
    elif SENSORDATA==0:
      if day==1 and value in favourable:
        return str(1)
      else:
        return str(0)