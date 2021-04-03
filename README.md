# This is an V/C++ Study

> V/C++ 공부하기.
>   > 1단계를 기준으로 단계별로 기능을 추가할 계획이다.

## 1. PuzzleGame.

### 1단계 [코드참조](https://github.com/malvr00/V-Cplusplus-review/tree/master/puzzleGame)
  
* 초기 실행 화면 모습이다.  

     <img src="https://user-images.githubusercontent.com/77275513/112713756-1c33a380-8f1a-11eb-8645-ac0d3ff53b48.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>   
  
* 게임시작 클릭 후 사진이 뒤섞이고, 플레이 시간 및 그림이동 수와 그림맞춘 수를 카운팅한다.   
      
     <img src="https://user-images.githubusercontent.com/77275513/112713908-05da1780-8f1b-11eb-8ec4-aff97af30a6c.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>
 
* 힌트부분을 클릭하면 완성했을 때의 원본사진이 5초동안 보여진다.

     <img src="https://user-images.githubusercontent.com/77275513/112714335-45096800-8f1d-11eb-9826-f287a9578255.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>

---

## 2-1. TetrisGame.


### 1단계 [코드참조](https://github.com/malvr00/V-Cplusplus-review/blob/master/tetrisGame/tetrisGameDlg.cpp)

* 초기 실행 화면 모습이다.
 
     <img src="https://user-images.githubusercontent.com/77275513/112959684-a3815100-917e-11eb-9d5c-a72a59b26a5d.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>   

* 게임시작 클릭 후 블럭이 떨어지고 떨어질때 마다 1점씩 점수가 증가한다. 상단에는 다음 블럭을 표시한다.
 
     <img src="https://user-images.githubusercontent.com/77275513/112959957-e93e1980-917e-11eb-834c-fc2161ffec1d.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>   

* 블럭을 1줄 완성하면 10점이 추가되고 완성된 줄은 삭제된다.
 
     <img src="https://user-images.githubusercontent.com/77275513/112960107-125eaa00-917f-11eb-9c99-b61dc08e1e35.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>
      
---
## 2-2. TetrisGame Multi 2인 (Sokect 활용)
> 현재 미완성
---

## 3. Socket 복습
> java socket 복습 하기전 v/c++ 소켓 복습
>   > Server와 Client 하나로 안만들고 따로따로 만들었다.

### Socket Socket [코드참조]()
* ClientSocket에서 메세지를 보내면 메세지를 화면에 띄우고, Server: 붙여 ClientSocket에 다시 보낸다.
* Message Receive는 Client Socket에 만든 클래스를 재사용했고, 새로 Socket을 상속받아 Message Accept를 사용자 Message 정의 후 사용[[코드참조]](https://github.com/malvr00/V-Cplusplus-review/blob/master/ServerSocket/CMyServerSocket.h)

     <img src="https://user-images.githubusercontent.com/77275513/113474031-39331e00-94a8-11eb-8271-880837b5ad1f.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>
     

### Client Socket [코드참조](https://github.com/malvr00/V-Cplusplus-review/tree/master/CleintSocket)
* 메세지를 보내면 Server문자가 붙여서 다시 Client소켓으로 보내도록 설계 하였다.
* Message Receive 부분은 Socket을 상속받아서[[코드참조]](https://github.com/malvr00/V-Cplusplus-review/blob/master/CleintSocket/CMySocket.h) 사용자 Message 정의 후 사용했다.

     <img src="https://user-images.githubusercontent.com/77275513/113472910-1b15ef80-94a1-11eb-889a-2cb63f4f1bea.PNG" width="450px" height="300px" title="100px" alt="RubberDuck"></img><br/>

## Socket Chatting Program (Portfolio)
> Chatting Program User 관리 및 서버관리 Socket
>  > User용 Client Chatting Program Socket

### 현재미완성.
