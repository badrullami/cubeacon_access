# Cubeacon Access Control Reader MQTT API

## A. Result of Scanning
MQTT published packet used to know result of scanning miFare card/cubeacon card.

Message structure to consider :

|channel | message structure|
|-------|---------|
|```bg/rc/[device_id]``` | ```{"[card_type]":"[uid]"}``` |

The packet contains following field of information :

|Info | Description |
|--------|----|
| device_id | 6 last digit of MAC address |
| card_type | card type of result from scanning  |
| uid | for cubeacon card  : 4 last digit uuid + 3 digit major + minor, for mifare : 6 digit card uid|
#

To get the published packet from the broker simply subscribe to the specified channel, see bellow example.
### Example 
Subscription example using mosquitto client:
```
mosquitto_sub -h [mqtt_broker] -p [mqtt_port] -u [mqtt_user] -P [mqtt_password] -t bg/rc/881494
```
Message example for cubeacon card:
```
{"beacon":"1aec1111223"}
```
Message example for mifare card:
```
{"mifare":"578637d8"}
```

## B. Access granting
Access granting use to allow the gate for open or reject using mqtt client with message format in JSON

Message structure :

|channel | message structure|
|-------|---------|
|```bg/[device_id]``` | ```{"command":"[access]"}``` |

The packet contains following field of information :

|Info | Description |
|--------|----|
| device_id | 6 last digit of MAC address |
| access | allow/reject  |
#

### Example
To granting the access, publish packet to specific channel. see example below
```
mosquitto_pub -h [mqtt_broker] -p [mqtt_port] -u [mqtt_user] -P [mqtt_password] -t bg/881494 -m {\"command\":\"allow\"}'
```

## C. New device connected
To find out which devices have just been connected to the network, we can monitor with subscribe packet from specific channel.

### Example

```
mosquitto_sub -h [mqtt_broker] -p [mqtt_port] -u [mqtt_user] -P [mqtt_password] -t bg/CH806
```
message from subscribtion channel is device ID that recently connected to the internet







