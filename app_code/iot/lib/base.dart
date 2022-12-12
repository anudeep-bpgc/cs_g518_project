import 'package:flutter/material.dart';
import 'package:flutter_switch/flutter_switch.dart';
import 'package:http/http.dart' as http;

class base extends StatefulWidget {
  const base({super.key});

  @override
  State<base> createState() => _baseState();
}

class _baseState extends State<base> {
 bool auto=true;
 bool manual=true;
  void func()async{
    final response = await http.get(Uri.parse('http://10.50.2.56:8081/get/auto'));
    print(response.statusCode);
    if(response.body=="2"){
      setState(() {
        auto=true;
      });
    }
    else{
      setState(() {
        auto=false;
      });
    }
    final res = await http.get(Uri.parse('http://10.50.2.56:8081/set/user/0'));
    print(res.statusCode);
    if(res.body=="1"){
      setState(() {
        manual=true;
      });
    }
    else{
      setState(() {
        manual=false;
      });
    }
    print('here');
  }
  @override
  void initState() {
    // TODO: implement initState
    func();
  }


  @override
  Widget build(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: Text(
          'IOT Project',
          style: TextStyle(color: Colors.white),
        ),
        backgroundColor: Colors.redAccent,
      ),
      body: Container(
        padding: EdgeInsets.all(10),
        width: double.infinity,
        height: double.infinity,
        child: Column(
          children: [
            SizedBox(height: 20,child: Container(height: 20,),),
            Text(auto?'Auto':'Manual',style: TextStyle(color: Colors.redAccent,fontSize: 32),),
            SizedBox(height: 20,child: Container(height: 20,),),
            FlutterSwitch(
              value: auto,
              onToggle: (value)async{
                setState((){
                  auto = !auto;
                  print(auto);
                });
                if(auto){
                        final response = await http.get(Uri.parse('http://10.50.2.56:8081/auto'));
                        print(response.statusCode);
                        print(response.body);
                  }
                  else{
                      final response = await http.get(Uri.parse('http://10.50.2.56:8081/set/user/0'));
                      print(response.statusCode);
                      if(response.body=="0"){
                        setState(() {
                          manual=false;
                        });
                      }
                      else if(response.body=="1"){
                        setState(() {
                          manual=true;
                        });
                      }
                  }
              },
              switchBorder: Border.all(color: Colors.redAccent),
            ),SizedBox(height: 20,child: Container(height: 20,),),
            Text(manual?'Outside':'In Shed',style: TextStyle(color: Colors.redAccent,fontSize: 32),),
            SizedBox(height: 20,child: Container(height: 20,),),
            FlutterSwitch(
              value: manual,
              disabled: auto,
              onToggle: (value)async{
                setState((){
                  manual = !manual;
                  print(manual);
                });
                if(manual){
                        final response = await http.get(Uri.parse('http://10.50.2.56:8081/set/user/1'));
                        print(response.statusCode);
                        print(response.body);
                        if(response.body=="0"){
                        setState(() {
                          manual=false;
                        });
                      }
                      else if(response.body=="1"){
                        setState(() {
                          manual=true;
                        });
                      }
                  }
                  else{
                      final response = await http.get(Uri.parse('http://10.50.2.56:8081/set/user/0'));
                      print(response.statusCode);
                      print(response.body);
                      if(response.body=="0"){
                        setState(() {
                          manual=false;
                        });
                      }
                      else if(response.body=="1"){
                        setState(() {
                          manual=true;
                        });
                      }
                  }
              },
              switchBorder: Border.all(color: Colors.redAccent),
            ),
          ],
        ),
      ),
    );
  }
}
