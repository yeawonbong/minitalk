# minitalk
The purpose of this project is to code a small data exchange program using UNIX signals.  
In this project, two different processes(server, and client) can exchange data through UNIX signals.

클라이언트-서버 프로세스간 시그널로 통신하는 프로그램.  
양방향 연결지향 통신으로, 연결된 client가 보낸 데이터를 모두 수신하면, sever가 client에 시그널을 보내 안정적으로 연결을 종료한다.  
통신 진행 중 다른 client의 연결시도가 발생할 경우 해당 프로세스는 대기시킨 뒤, 통신중이던 client의 연결이 완전히 종료된 후 연결한다. 

# 실행방법
1. `make`
2. `./server`
3. `./client [server_PID] [data_to_send]`  

![gif_short](https://user-images.githubusercontent.com/75327385/151111557-01bddcf5-efef-49c8-9091-8857722dfbe5.gif)
![gif_long](https://user-images.githubusercontent.com/75327385/151112910-9b824f76-88c8-4649-9650-b952e3a0bce6.gif)
