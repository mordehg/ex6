#include <iostream>
#include "Driver.h"
#include "Udp.h"
#include "Tcp.h"
#include "Validation.h"

using namespace std;
using namespace boost::iostreams;
using namespace boost::archive;

vector<string> inputParser() {
    vector<string> data;
    string input;
    cin >> input;
    int startPos = 0;
    int i = 0;
    string current_str;
    while (input.length() != i) {
        if (input[i] == ',') {
            int len = i-startPos;
            current_str = input.substr(startPos,len);
            data.push_back(current_str);
            startPos = i+1;
        }
        i++;
    }
    current_str = input.substr(startPos,i-startPos+1);
    data.push_back(current_str);
    return data;
}


int main(int argc, char *argv[]) {
    Validation* valid = new Validation(false);
    vector<string> driver_data = inputParser();
    if (!valid->validDriverLength(driver_data.size()))
        exit(0);
    int id = atoi(driver_data[0].c_str());
    int age = atoi(driver_data[1].c_str());
    char statusLetter = driver_data[2].c_str()[0];
    int experience = atoi(driver_data[3].c_str());
    int cabId = atoi(driver_data[4].c_str());
    Status status = Status(statusLetter);
    if (!valid->validDreiver(id, age, status,experience,cabId))
        exit(0);

    Driver* driver = new Driver(id, age, status, experience, cabId);

    // create new socket
    //Socket *udp = new Udp(0, atoi(argv[2]));
    Socket *sock=new Tcp(0,atoi(argv[2]));
    sock->initialize();
    char buffer[9999];

    // serial driver object to string
    string serial_str;
    back_insert_device<std::string> inserter(serial_str);
    stream<boost::iostreams::back_insert_device<std::string>> s(inserter);
    binary_oarchive oa(s);
    oa << driver;
    s.flush();

    // send driver object to server
    sock->sendData(serial_str, 0);
    // get a cab

    // get a cab serial string from server and add it to driver.
    sock->reciveData(buffer, sizeof(buffer), 0);
    Cab* cab;
    boost::iostreams::basic_array_source<char> device(buffer, sizeof(buffer));
    boost::iostreams::stream<boost::iostreams::basic_array_source<char> > stream1
            (device);
    boost::archive::binary_iarchive ia(stream1);
    ia >> cab;
    //cout << cab->getCabId() <<endl;
    driver->setCab(cab);


    //get from server point of the next step at path
    int b=1;
    while(b!=0){
        b=driver->setDataDriver(sock);
    }
    delete(driver);
    delete(cab);
    delete (sock);
    delete(valid);
    return 0;
}