#include<bits/stdc++.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0)
#define f(i,m,n) for(int i = (m); i < (n); i++)
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
#define all(v) sort(v.begin(),v.end())
#define sz(v) int(v.size())
const int MOD=1e9+7;
const int mod= 998244353;
typedef long long ll;
typedef vector<int> vi; 
typedef vector<ll> vll; 
typedef vector<pair<int,int>> vii; 
class Observable;
class Observer{
    public:
        virtual ~Observer() = default;
        virtual void update(Observable&) = 0;
        friend class DisplayDevice;
};
class Observable{
  private:
  vector<Observer*> vo;
  public:
  virtual ~Observable() = default;
	void notify()  {
		for(auto &o:vo){
			o->update(*this);
		}
	}
  void attach(Observer& o){
     vo.push_back(&o);
  }
  void detach(Observer& o){
    vo.erase(std::remove(vo.begin(), vo.end(), &o));
  }
};
class WeatherStationObservable : public Observable {
	private:
    double temperature;
    double pressure;
    double humidity;
	public: 
  double getTemperature()
    const {return temperature;}
  
  double getPressure()
    const {return pressure;}
   
  double getHumidity()
    const {return humidity;}
	
  void setParameters(double temp, double hum, double pres){
    temperature=temp;
    humidity=hum;
    pressure=pres;
    notify();
  }
	
};

class DisplayDevice{
	private:
	double temperature;
	double pressure;
	double humidity;
	public:
	void displayAll(){
	   cout<<"current temperature is: "<<temperature<<endl;
	   cout<<"current pressure is: "<<pressure<<endl;
	   cout<<"current humidity is: "<<humidity<<endl;
	   
	}
	
	void setTemperature(double temp){
		temperature = temp;
	}
	void setPressure(double press){
		pressure = press;
	}
	void setHumidity(double hum){
		humidity = hum;
	}
	
	
	
	
};
class HumidityObserver : public Observer {
  private:
  WeatherStationObservable& s;
  DisplayDevice* d;
  public:
     explicit HumidityObserver(WeatherStationObservable& x,DisplayDevice* e) : s(x) { s.attach(*this); d=e;}
    ~HumidityObserver() { s.detach(*this); }
    void update(Observable& theChangedSubject) override
     {
         if (&theChangedSubject == &s) {
             draw();
         }
     }
     void draw(){
       double hum = s.getHumidity();
        d->setHumidity(hum);
     }

};
class PressureObserver : public Observer {
  private:
  WeatherStationObservable& s;
  DisplayDevice* d;
  public:
     explicit PressureObserver(WeatherStationObservable& x,DisplayDevice* e) : s(x) { s.attach(*this);d=e;}
     friend class DisplayDevice;
    ~PressureObserver() { s.detach(*this); }
    void update(Observable& theChangedSubject) override
     {
         if (&theChangedSubject == &s) {
             draw();
         }
     }
        void draw(){
        double pre = s.getPressure();
        d->setPressure(pre);
     }
};
class TemperatureObserver : public Observer {
  private:
  WeatherStationObservable& s;
  DisplayDevice* d;
  public:
     friend class DisplayDevice;
     explicit TemperatureObserver (WeatherStationObservable& x, DisplayDevice* e) : s(x) { s.attach(*this); d=e;} 
    ~TemperatureObserver () { s.detach(*this); }
    void update(Observable& theChangedSubject) override
     {
         if (&theChangedSubject == &s) {
             draw();
         }
     }
     void draw(){
        double te = s.getTemperature();
        d->setTemperature(te);
     }
};


int main() {
    fastio;
    WeatherStationObservable w;
    DisplayDevice* d=new DisplayDevice();
    TemperatureObserver t(w,d);
    PressureObserver p(w,d);
    HumidityObserver h(w,d);
    w.setParameters(10,20,30);


}