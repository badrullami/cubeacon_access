const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>Reader</title></head>
<body>
  <h1 style="color:blue;font-family:arial">READER CONFIG PAGE</h1>
  <h2>Device Configuration</h2><br>
  <h3>Access Point Setting</h3>
  <form  action = "/config/network_ap" method="post"> 
    <table border= "0" >
      <tr>
        <td>AP SSID</td>
        <td>: <input type="text" name="ssid" id="ssid" value=%AP_SSID%></td>
      </tr>
      <tr>
        <td>AP Password</td>
        <td>: <input type="password" name="password" id="password" value=%AP_PASSWORD%></td>
      </tr>
            <tr>
        
      </tr> 
    </table>
    <br>
    <input type="submit" value="Save AP Network Config">
  </form> 
  <br>
  <h3>Station Setting</h3>
  <form action = "/config/network_sta" method="post"> 
    <table border= "0" >
      <tr>
        <td>SSID</td>
        <td>: <input type="text" name="ssid" id="ssid" value=%SSID%></td>
      </tr>
      <tr>
        <td>Password</td>
        <td>: <input type="password" name="password" id="password" value=%PASSWORD%></td>
      </tr>
            <tr>
        <td><br></td>
      </tr>
            <tr>
        <td><input type="radio" name="network_mode" id=dhcp value="DHCP" onchange="ip_form()"> DHCP<br></td>
        <td><input type="radio" name="network_mode" id=static value="Static" onchange="ip_form()"> Static<br></td>
      </tr>
      <tr id="table_row_ip">
        <td>ip</td>
        <td>: <input type="text" name="ip" id="ip_input" minlength="7" maxlength="15" size="15" value=%IP% pattern="^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$"></td>
      </tr>
      <tr id="table_row_gateway">
        <td>gateway</td>
        <td>: <input type="text" name="gateway" id="gateway_input" minlength="7" maxlength="15" size="15" value=%GATEWAY% pattern="^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$"></td>
      </tr>
      <tr id="table_row_netmask">
        <td>netmask</td>
        <td>: <input type="text" name="netmask" id="netmask_input" minlength="7" maxlength="15" size="15" value=%NETMASK% pattern="^((\d{1,2}|1\d\d|2[0-4]\d|25[0-5])\.){3}(\d{1,2}|1\d\d|2[0-4]\d|25[0-5])$"></td>
      </tr> 
    </table>
    <br>
    <input type="submit" value="Save STNetwork Config">
  </form> 
  
    <br>
<p>
  <a href="/reboot"><button class="button">Reboot</button>;
</p>  
</body>
</html>)rawliteral";
