#include <WiFi.h>
#include <HTTPClient.h>

#define WIFINAME "WHY KE"
#define WIFIPASS "wahyu12345"
#define IDROBOT "M2"
#define URLWEB "https://ip.bywahjoe.com/post.php"

//#define APIKEY "sendIP4"
String APIKEY="sendIP4";
extern String myIP = "";

void postWebIP(String dataIP, String id = IDROBOT);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(WIFINAME, WIFIPASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  myIP = WiFi.localIP().toString();
  postWebIP(myIP);
}

void loop() {
  // put your main code here, to run repeatedly:

}
void postWebIP(String dataIP, String id) {
  HTTPClient postWeb;
  
  postWeb.begin(URLWEB);
  postWeb.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  String dataku = "apiKEY=" + APIKEY + "&MYID=" + IDROBOT + "&MYIP=" + dataIP;
  Serial.println(dataku);
  
  int httpResponseCode = postWeb.POST(dataku);
//UNCOMENT TO CEK ERROR  
//   if (httpResponseCode>0) {
//      Serial.print("HTTP Response code: ");
//      Serial.println(httpResponseCode);
//    }
//    else {
//      Serial.print("Error code: ");
//      Serial.println(httpResponseCode);
//    }
    postWeb.end();
  

}
