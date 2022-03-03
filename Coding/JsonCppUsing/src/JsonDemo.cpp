#include <iostream>
#include <string>
#include "json.h"

using namespace std;


const char * type_token = "type";
const char * orthography_token = "orthography";
const char * is_final_token = "is_final";
const char * area_token = "area";


int ParseAsrFromString(const std::string& str){
  Json::Reader reader;
  Json::Value root;
  if (reader.parse(str.c_str(), root)){
    std::string asrResult = root["orthography"].asString();
    cout << "asrResult:" << asrResult << endl;
    int is_final = root["is_final"].asInt();
    cout << "is_final:" <<is_final << endl;
  }
  return 0;
}

int ParseNluFromString(const std::string& str) {
  Json::Reader reader;
  Json::Value root;
  if (reader.parse(str.c_str(), root)) {
    string name = root["onboard"]["intents"][0]["name"].asString();
    string domain = root["onboard"]["intents"][0]["domain"].asString();
    string slots = root["onboard"]["intents"][0]["slots"].toStyledString();
    cout << "nluResult name is " << name << endl;
    cout << "nluResult domain is " << domain << endl;
    cout << "nluResult slots is " << slots << endl;
  }
  return 0;
}


int ParseWakeUpFromString(const std::string& str) {
  Json::Reader reader;
  Json::Value root;
  if (reader.parse(str.c_str(), root)) {
    std::string nluResult = root["orthography"].asString();
    cout << "WakeUp Result is " << nluResult << endl;
  }
  return 0;
}

int ParseWakeUpCustomizedFromString(const std::string& str) {
  Json::Reader reader;
  Json::Value root;
  if (reader.parse(str.c_str(), root)) {
    std::string type = root["type"].asString();
    cout << "WakeUp Customized type is " << type << endl;

    std::string orthography = root["orthography"].asString();
    cout << "WakeUp Customized Result is " << orthography << endl;

    std::string area = root["area"].asString();
    cout << "WakeUp Customized area is " << area << endl;
  }
  return 0;
}


void BuildCustomizedNluResult(const std::string& raw_nlu_result){
  Json::Value arrayObj;
  Json::Value type_json, status_json, conf_json, orthography_json, domain_json, intent_json, slots_json;

  Json::Reader reader;
  Json::Value root;
  if (reader.parse(raw_nlu_result.c_str(), root)) {

    cout << "root is " << root.toStyledString() << endl;

    // string type = root["type"].asString();
    // string status = root["onboard"]["status"].asString();
    // string conf = root["conf"]["onboard"].asString();
    // string orthography = root["onboard"]["orthography"].asString();
    // string intent = root["onboard"]["intents"][0]["name"].asString();
    // string domain = root["onboard"]["intents"][0]["domain"].asString();
    // string slots = root["onboard"]["intents"][0]["slots"].toStyledString();

    // cout << "nluResult type: " << type << " status: " << status << "conf " << conf << endl;
    // cout << "nluResult orthography is " << orthography << endl;
    // cout << "nluResult intent is " << intent << endl;
    // cout << "nluResult domain is " << domain << endl;
    // cout << "nluResult slots is " << slots << endl;

    type_json["type"] = root["type"];
    status_json["status"] = root["onboard"]["status"];
    orthography_json["orthography"] = root["onboard"]["orthography"];
    domain_json["domain"] = root["onboard"]["intents"][0]["domain"];
    intent_json["intent"] = root["onboard"]["intents"][0]["name"];
    slots_json["slots"] = root["onboard"]["intents"][0]["slots"];
    arrayObj.append(type_json);
    arrayObj.append(status_json);
    arrayObj.append(domain_json);
    arrayObj.append(intent_json);
    arrayObj.append(slots_json);
    string result = arrayObj.toStyledString();
    cout << "build result string is " << result << endl;
  }
}



int main(){

    string asrResult = "{\"type\": \"asr\", \"orthography\": \"play music\", \"is_final\": true}";
    ParseAsrFromString(asrResult);

    string wakeupResult = "{\"type\": \"wuw_sds\", \"orthography\": \"Hey World\", \"audio_info\": {}, \"conf\": 6000, \"area\": \"SEAT_ROW_1_LEFT\"}";
    ParseWakeUpFromString(wakeupResult);

    string wakeupCustomized = "{ \"type\": \"wuw_customized\", \"orthography\": \"Hello World\", \"audio_info\": {}, \"conf\": 6000, \"area\": \"SEAT_ROW_1_LEFT\"}";
    ParseWakeUpCustomizedFromString(wakeupCustomized);

    string nluResult = "{\"type\": \"shortcut\", \"recommendation\": \"onboard\", \"audio_info\": {}, \"onboard\": { \"status\": \"OK\", \"status_description\": \"\", \"conf\": 9000, \"orthography\": \"open the sunroof\", \"intents\": [{ \"name\": \"settings_and_control:open:windows\", \"domain\": \"command_and_control\", \"orthography\": \"open the sunroof\", \"slots\": { \"car_part\": [{ \"literal\": \"sunroof\", \"canonical\": \"sunroof\" }] } }] }, \"offboard\": {}}";

    ParseNluFromString(nluResult);

    BuildCustomizedNluResult(nluResult);

    return 0;
}


