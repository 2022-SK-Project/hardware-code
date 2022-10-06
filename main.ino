#include <ESP8266WiFi.h>
#include <Servo.h>
#include <ESP8266WebServer.h>
Servo servo;

const char* ssid = "TEST_SSID";
const char* pw = "test1234";

const char Main[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
        * {
  margin: 0;
  padding: 0;
}
a {
  text-decoration: none;
  color: black;
}
body {
  background-color: rgb(244, 244, 244);
}
.div {
  width: 100%;
}

/* header */
header {
  /* height: 87px; */
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 25px 28px;
  margin-bottom: 25px;
}
header > a > img {
  width: 30px;
  height: 30px;
}
.my_chip > a > img {
  width: 24px;
  height: 24px;
}

/* nav 문구 */
nav {
  margin: 0 0 33px 24px;
  font-size: 24px;
}

/* section */
section {
  display: flex;
  align-items: center;
  flex-direction: column;
}
.chip-circle {
  width: 235px;
  height: 235px;
  border-radius: 50%;
  border-top: 2px solid #fa5252;
  border-left: 2px solid #fa5252;
  display: flex;
  flex-direction: column;
  align-items: center;
  margin-bottom: 24px;
  box-shadow: inset 0px -10px 5px 0px #ffffff, inset 0px 10px 10px 0px #00000040;
}
.chip-circle > img {
  width: 24px;
  height: 24px;
  margin-top: 50px;
}
.chip-circle > p {
  font-size: 15;
  color: #a1a1a1;
  margin-top: 17px;
}
.chip-circle > b {
  font-size: 72px;
  color: #444444;
}
.red-arrow {
  width: 14px;
  height: 14px;
  margin-bottom: 11px;
}
section > p {
  font-size: 16px;
  color: #707070;
}

/* footer */
.mySlides {
  height: 100px;
  border: 2px solid rgba(226, 226, 226, 1);
  border-radius: 10px;
  background-color: white;
  margin: 67px 30px 0 30px;
  padding: auto;
}
.mySlides > p {
  font-size: 18px;
  float: left;
  padding-left: 20px;
  padding: 15px 0 0 24px;
}
.mySlides > img {
  width: 100px;
  height: 90px;
  margin: 0 26px;
  float: right;
}

/* 슬라이드 */
#slider {
  width: 100%;
  height: 100%;

  margin: 0 auto;
  border: 10px solid transparent;
  padding: 0px;

  z-index: 100;
  overflow: hidden;
  white-space: nowrap;
  box-sizing: border-box;
}
#slider > li {
  width: 100%;
  height: 100%;

  position: relative;
  display: inline-block;
  overflow: hidden;
  font-size: 15px;
  font-size: initial;
  line-height: normal;
  transition: all 0.3s cubic-bezier(0.3, 1.2, 0.65, 1);

  /* Slide css animation */
  background-size: cover;
  vertical-align: top;
  box-sizing: border-box;
  white-space: normal;
}
    </style>
</head>

<body>
    <div class="div">
        <header>
            <a href="./MyPage"><img src="https://user-images.githubusercontent.com/108206338/191177050-08b3fe8e-290e-4f72-8912-8c232f6f8502.png" alt="person_icon"></a>
            <div class="my_chip">
                <a href="./Management"><img src="https://user-images.githubusercontent.com/108206338/191178659-820c8ca6-13ef-483c-aa73-83dc5afd90d1.png" alt=""></a>
            </div>
        </header>

        <nav>
            <p>장송하님의 목표 배출일까지,<br>
                3일 남았어요.</p>
        </nav>

        <section>
            <!-- 동그라미 -->
            <a href="./Unlock" class="chip-circle">
                <img src="https://user-images.githubusercontent.com/108206338/191177419-55ed7da4-43c6-4e32-9b00-a586cfd74f0b.png" alt="locker">
                <p>My Chip</p>
                <b>4</b>
            </a>

            <img class="red-arrow" src="https://user-images.githubusercontent.com/108206338/191177483-1d26f446-9940-4f97-88d1-d4288cdb8ae7.png" alt="red-arrow">
            <p>이곳을 터치해 굿유를 여세요</p>
        </section>


        <footer>
            <div class="mySlides fade">
                <p>과일 씨는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191177620-d09aee20-56f4-4768-9cf4-d1751387db6b.png">
            </div>

            <div class="mySlides fade">
                <p>생선 가시는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191177743-ee28b23f-db59-4ef2-a1c1-e1e5aeab49b4.png">
            </div>

            <div class="mySlides fade">
                <p>뼈는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191177780-f91d8a64-281b-4816-a020-3fc360661cfd.png">
            </div>
        </footer>

        <br>

        <div style="text-align:center">
            <span class="dot"></span>
            <span class="dot"></span>
            <span class="dot"></span>
        </div>
    </div>

    <script>
        var slideIndex = 0;
        showSlides();

        function showSlides() {
            var i;
            var slides = document.getElementsByClassName("mySlides");
            var dots = document.getElementsByClassName("dot");
            for (i = 0; i < slides.length; i++) {
                slides[i].style.display = "none";
            }
            slideIndex++;
            if (slideIndex > slides.length) { slideIndex = 1 };
            for (i = 0; i < dots.length; i++) {
                dots[i].className = dots[i].className.replace(" active", "");
            }
            slides[slideIndex - 1].style.display = "block";
            dots[slideIndex - 1].className += " active";
            setTimeout(showSlides, 2000);
        }
    </script>
    
</body>

</html>
)=====";

const char Index[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
        * {
  margin: 0;
  padding: 0;
}
a {
  text-decoration: none;
  color: black;
}
body {
  background-color: rgb(244, 244, 244);
}
.div {
  width: 100%;
}

/* header */
header {
  /* height: 87px; */
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 25px 28px;
  margin-bottom: 25px;
}
header > a > img {
  width: 30px;
  height: 30px;
}
.my_chip > a > img {
  width: 24px;
  height: 24px;
}

/* nav 문구 */
nav {
  margin: 0 0 33px 24px;
  font-size: 24px;
}

/* section */
section {
  display: flex;
  align-items: center;
  flex-direction: column;
}
.chip-circle {
  width: 235px;
  height: 235px;
  border-radius: 50%;
  border-top: 2px solid #fa5252;
  border-left: 2px solid #fa5252;
  display: flex;
  flex-direction: column;
  align-items: center;
  margin-bottom: 24px;
  box-shadow: inset 0px -10px 5px 0px #ffffff, inset 0px 10px 10px 0px #00000040;
}
.chip-circle > img {
  width: 24px;
  height: 24px;
  margin-top: 50px;
}
.chip-circle > p {
  font-size: 15;
  color: #a1a1a1;
  margin-top: 17px;
}
.chip-circle > b {
  font-size: 72px;
  color: #444444;
}
.red-arrow {
  width: 14px;
  height: 14px;
  margin-bottom: 11px;
}
section > p {
  font-size: 16px;
  color: #707070;
}

/* footer */
.mySlides {
  height: 100px;
  border: 2px solid rgba(226, 226, 226, 1);
  border-radius: 10px;
  background-color: white;
  margin: 67px 30px 0 30px;
  padding: auto;
}
.mySlides > p {
  font-size: 18px;
  float: left;
  padding-left: 20px;
  padding: 15px 0 0 24px;
}
.mySlides > img {
  width: 100px;
  height: 90px;
  margin: 0 26px;
  float: right;
}

/* 슬라이드 */
#slider {
  width: 100%;
  height: 100%;

  margin: 0 auto;
  border: 10px solid transparent;
  padding: 0px;

  z-index: 100;
  overflow: hidden;
  white-space: nowrap;
  box-sizing: border-box;
}
#slider > li {
  width: 100%;
  height: 100%;

  position: relative;
  display: inline-block;
  overflow: hidden;
  font-size: 15px;
  font-size: initial;
  line-height: normal;
  transition: all 0.3s cubic-bezier(0.3, 1.2, 0.65, 1);

  /* Slide css animation */
  background-size: cover;
  vertical-align: top;
  box-sizing: border-box;
  white-space: normal;
}
    </style>
</head>

<body>
    <div class="div">
        <header>
            <a href="./MyPage"><img src="https://user-images.githubusercontent.com/108206338/191177050-08b3fe8e-290e-4f72-8912-8c232f6f8502.png" alt="person_icon"></a>
            <div class="my_chip">
                <a href="./Management"><img src="https://user-images.githubusercontent.com/108206338/191178659-820c8ca6-13ef-483c-aa73-83dc5afd90d1.png" alt=""></a>
            </div>
        </header>

        <nav>
            <p>장송하님의 목표 배출일까지,<br>
                3일 남았어요.</p>
        </nav>

        <section>
            <!-- 동그라미 -->
            <a href="./Unlock" class="chip-circle">
                <img src="https://user-images.githubusercontent.com/108206338/191177419-55ed7da4-43c6-4e32-9b00-a586cfd74f0b.png" alt="locker">
                <p>My Chip</p>
                <b>4</b>
            </a>

            <img class="red-arrow" src="https://user-images.githubusercontent.com/108206338/191177483-1d26f446-9940-4f97-88d1-d4288cdb8ae7.png" alt="red-arrow">
            <p>이곳을 터치해 굿유를 여세요</p>
        </section>


        <footer>
            <div class="mySlides fade">
                <p>과일 씨는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191177620-d09aee20-56f4-4768-9cf4-d1751387db6b.png">
            </div>

            <div class="mySlides fade">
                <p>생선 가시는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191177743-ee28b23f-db59-4ef2-a1c1-e1e5aeab49b4.png">
            </div>

            <div class="mySlides fade">
                <p>뼈는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191177780-f91d8a64-281b-4816-a020-3fc360661cfd.png">
            </div>
        </footer>

        <br>

        <div style="text-align:center">
            <span class="dot"></span>
            <span class="dot"></span>
            <span class="dot"></span>
        </div>
    </div>

    <script>
        var slideIndex = 0;
        showSlides();

        function showSlides() {
            var i;
            var slides = document.getElementsByClassName("mySlides");
            var dots = document.getElementsByClassName("dot");
            for (i = 0; i < slides.length; i++) {
                slides[i].style.display = "none";
            }
            slideIndex++;
            if (slideIndex > slides.length) { slideIndex = 1 };
            for (i = 0; i < dots.length; i++) {
                dots[i].className = dots[i].className.replace(" active", "");
            }
            slides[slideIndex - 1].style.display = "block";
            dots[slideIndex - 1].className += " active";
            setTimeout(showSlides, 2000);
        }
    </script>
    
</body>

</html>
)=====";

const char Unlock[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>굿유-메인페이지</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
</head>

<body>
    <div class="div">
        <header>
            <a href="./MyPage"><img src="https://user-images.githubusercontent.com/108206338/191181480-e2012f8a-f3cb-43c5-86c8-cbb3f84a4ec6.png" alt="사람 아이콘"></a>
            <div class="my_chip">
                <a href="./Management"><img src="https://user-images.githubusercontent.com/108206338/191181428-2bbf8f62-1d37-485c-8321-5b8ec3d983a5.png" alt=""></a>
            </div>
            <style>
                *{
    margin: 0;
    padding: 0;
}
a{
    text-decoration: none;
    color: black;
}
body{
    background-color: rgb(244, 244, 244);
}
.div{
    width: 100%;
}

/* header */
header{
    /* height: 87px; */
    display: flex;
    justify-content: space-between;
    align-items: center;
    padding: 25px 28px;
    margin-bottom: 25px;
}
header > a > img{
    width: 30px;
    height: 30px;
}
.my_chip > a{
    font-size: 18px;
}
.my_chip > a > img{
    width: 24px;
    height: 24px;
}

/* nav 문구 */
nav{
    margin: 0 0 33px 24px;
    font-size: 24px;
}
/* section */
section{
    display: flex;
    align-items: center;
    flex-direction: column;
}
.chip-circle{
    width: 235px;
    height: 235px;
    border-radius: 50%;
    border-top: 2px solid #4F8BFF;
    border-left: 2px solid #4F8BFF;
    display: flex;
    flex-direction: column;
    align-items: center;
    margin-bottom: 24px;
    box-shadow:inset 0px -10px 5px 0px #FFFFFF,inset 0px 10px 10px 0px #00000040;
}
.chip-circle > img{
    width: 24px;
    height: 24px;
    margin-top: 50px;
}
.chip-circle > p{
    font-size: 15;
    color: #A1A1A1;
    margin-top: 17px;
}
.chip-circle > b{
    font-size: 72px;
    color: #444444;
}
.blue-arrow{
    width: 14px;
    height: 14px;
    margin-bottom: 11px;
}
section > p{
    font-size: 16px;
    color: #707070;
}

/* footer */
.mySlides{
    height: 100px;
    border: 2px solid rgba(226, 226, 226, 1);
    border-radius: 10px;
    background-color: white;
    margin: 67px 30px 0 30px;
}
.mySlides > p{
    font-size: 18px;
    float: left;
    padding-left: 20px;
    padding: 15px 0 0 24px;
}
.mySlides > img{
    width: 100px;
    height: 90px;
    margin: 0 26px;
    float: right;
}

/* 슬라이드 */
/* #slider {
    width: 100%;
    height: 100%;

    margin: 0 auto;
    border: 10px solid transparent;
    padding: 0px;

    z-index: 100;
    overflow: hidden;
    white-space: nowrap;
    box-sizing: border-box;
  }
#slider > li {
    width: 100%;
    height: 100%;

    position: relative;
    display: inline-block;
    overflow: hidden;
    font-size: 15px;
    font-size: initial;
    line-height: normal;
    transition: all 0.3s cubic-bezier(0.3, 1.2, 0.65, 1);
    
    
    background-size: cover;
    vertical-align: top;
    box-sizing: border-box;
    white-space: normal;
  } */
            </style>
        </header>

        <nav>
            <p>굿유가 열렸습니다.<br>
                쓰레기를 배출해주세요.</p>
        </nav>

        <section>
            <!-- 동그라미 -->
            <a href="./Index" class="chip-circle">
                <img src="https://user-images.githubusercontent.com/108206338/191690441-78067328-9ccb-4e9d-b239-55d06b0798f0.png" alt="자물쇠 아이콘">
                <p>My Chip</p>
                <b>4</b>
            </a>

            <img class="blue-arrow" src="https://user-images.githubusercontent.com/108206338/191690904-e7880b2d-2a16-497a-9e7f-0b8e6d692654.png" alt="">
            <p>이곳을 터치해 굿유를 닫으세요</p>
        </section>

        <footer>
            <div class="mySlides fade">
                <p>과일 씨는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191181583-352d2cb2-e0aa-48db-a405-2b9e8c3a42c4.png">
            </div>

            <div class="mySlides fade">
                <p>생선 가시는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191181710-d4eeb85e-3afa-480a-94ad-5ea6bede62b9.png">
            </div>

            <div class="mySlides fade">
                <p>뼈는<br>
                    <b>일반쓰레기</b>인거<br>
                    알고계시죠?
                </p>
                <img src="https://user-images.githubusercontent.com/108206338/191181661-aad681e6-dda4-4160-8cf9-932162670dcd.png">
            </div>
        </footer>

        <br>

        <div style="text-align:center">
            <span class="dot"></span>
            <span class="dot"></span>
            <span class="dot"></span>
        </div>
    </div>

    <script>
        var slideIndex = 0;
        showSlides();

        function showSlides() {
            var i;
            var slides = document.getElementsByClassName("mySlides");
            var dots = document.getElementsByClassName("dot");
            for (i = 0; i < slides.length; i++) {
                slides[i].style.display = "none";
            }
            slideIndex++;
            if (slideIndex > slides.length) { slideIndex = 1 }
            for (i = 0; i < dots.length; i++) {
                dots[i].className = dots[i].className.replace(" active", "");
            }
            slides[slideIndex - 1].style.display = "block";
            dots[slideIndex - 1].className += " active";
            setTimeout(showSlides, 2000);
        }
    </script>
</body>

</html>
)=====";

const char Management[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>기기관리</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
        *{
    margin: 0;
    padding: 0;
}
a{
    text-decoration: none;
    color: black;
}
body{
    background-color: rgb(244, 244, 244);
}
.div{
    height: 756px;
    background-color: rgb(244, 244, 244);
    display: flex;
    flex-direction: column;
    align-items: center;
}

/* top */
.top{
    height: 24px;
    display: flex;
    justify-content: flex-end;
    align-items: center;
}
.top > i{
    padding: 0 6px;
    font-size: 13px;
}
.top > p{
    padding-right: 5px;
    font-size: 14px;
}

/* 마이페이지 */
.mypage{
    width: 100%;
    padding-bottom: 10px;
    border-bottom: 2px solid rgb(244, 244, 244);
    background-color: white;
}
.mypage > a > i{
    float: left;
    margin: 37px 0 0 37px;
}
h4{
    font-size: 20px;
    padding: 32px 37px 0 0;
    text-align: center;
}

/* 기기관리 선택 */
.input-container{
    width: 90%;
    margin: 13px 0 5px 0;
}
.liter{
    font-size: 12px;
    padding-left: 2px;
}
.input-box{
    width: 100%;
    height: 71px;
    border: 1px solid #ffbaba;
    border-radius: 8px;
    background-color: white;
    margin: 2px auto 10px auto;
    padding: 14px 24px;
    display: flex;
    justify-content: space-between;
    align-items: center;
}
.input-box > div > input{
    accent-color:rgba(250, 82, 82, 1);
    width: 24px;
    height: 24px;
    margin: 5px 15px 0 0;
    float: left;
}

/* 버튼으로 변경 */
.input-box > a{
    width: 56px;
    height: 25px;
    background-color: #FF9A9A;
    font-size: 13px;
    border-radius: 3px;
    margin-left: 120px;
    padding-top: 5px;
    box-sizing: border-box;
}
.input-box > div > label{
    font-size: 15px;
}
.input-box  div > small{
    font-size: 12px;
    color: #7C7C7C;
}
.modal-bg{
    width: 100%;
    height: 100%;
    background-color: rgba(0, 0, 0, 0.5);
    position: absolute;
    margin: 0 auto;
    display: none;
}
.white-box{
    width: 70%;
    height: 260px;
    background-color: white;
    position: relative;
    left: 50%;
    margin-left: -35%;
    top: 200px;
    border-radius: 10px;
    box-sizing: border-box;
    padding: 30px;
}
.white-box > hr{
    border: none;
    border-top: 1px solid black;
    margin-bottom: 15px;
}
.white-box > input{
    width: 70%;
    height: 35px;
    margin: 5px 0;
    padding-left: 10px;
    background-color: lightgray;
    border: none;
    border-radius: 5px;
}
.white-box > button{
    width: 50%;
    height: 35px;
    margin: 10px 0 0 25%;
    background-color: black;
    color: white;
    border: none;
    border-radius: 5px;
}
.show{
    display: block;
}

/* 추가하기 */
#plus{
    width: 100%;
    height: 50px;
    background-color: white;
    border-radius: 10px;
    border: 0.5px solid #b7b7b7;
}

.on-off{
    width: 7px;
    height: 7px;
    background-color: #7C7C7C;
}
    </style>
</head> 
<body>
    <div class="div">
        <!-- 제목 -->
        <div class="mypage">
            <a href="./"><i class="fa-solid fa-angle-left"></i></a>
            <h4>기기관리</h4>
        </div>

        <!-- 기기 선택 -->
        <div class="input-container">
            <button class="input-box">
                <input class="checked" type="radio" id="1" name="goodyou" checked="checked">
                <label for="1">굿유 1</label>
                <br>
                <small>사용중</small>
            </button>

            <br>

            <button class="input-box">
                <input type="radio" id="2" name="goodyou">
                <label for="2">굿유 2</label>
                <br>
                <small>사용중</small>
            </button>

            <br>

            <button class="input-box">
                <input type="radio" id="3" name="goodyou">
                <label for="3">굿유 3</label>
                <br>
                <small>사용중</small>
            </button>
        </div>
    </div>
</body>
</html>
)=====";

const char Chip[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="ko">

<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
        * {
  margin: 0;
  padding: 0;
}
a {
  text-decoration: none;
  color: black;
}
/* top */
.top {
  width: 100%;
  height: 24px;
  display: flex;
  justify-content: flex-end;
  align-items: center;
}
.top > i {
  padding: 0 6px;
  font-size: 13px;
}
.top > p {
  padding-right: 5px;
  font-size: 14px;
}

/* 마이페이지 */
.mypage > a > i {
  float: left;
  margin: 5px 0 0 37px;
}
h4 {
  font-size: 20px;
  margin: 32px 37px 0 0;
  text-align: center;
}

/* 칩 개수 부분 */
.chip_box {
  height: 160px;
  margin-top: 47px;
  display: flex;
  justify-content: space-around;
  align-items: center;
}
.chip_box > img {
  width: 130px;
  height: 130px;
}
.chip > p {
  font-size: 22px;
}
.chip > b {
  font-size: 40px;
  padding-left: 25px;
  color: #ff2121;
}

/* 칩 구매 버튼 */
.buyBar {
  margin: 24px 30px;
  text-align: left;
  display: flex;
  justify-content: space-between;
}
.buyBar > p {
  font-size: 15px;
}
.buyBar > button {
  width: 65px;
  height: 20px;
  font-size: 13px;
  border: 1px solid #dadada;
  border-radius: 24px;
  background-color: white;
}
hr {
  border: 0px;
  border-bottom: 1px solid rgba(224, 224, 224, 1);
  margin: 0 30px;
}
.hr {
  border-bottom: 1.5px solid rgba(224, 224, 224, 1);
}

    </style>
</head>

<body>
    <div class="div">
        <!-- 제목 -->
        <div class="mypage">
            <a href="./MyPage"><i class="fa-solid fa-angle-left"></i></a>
            <h4>충전하기</h4>
        </div>

        <!-- 칩 개수-->
        <div class="chip_box">
            <img src="https://user-images.githubusercontent.com/108206338/191417874-78ee7af3-dd81-44d4-94d4-352f6c2a845c.png" alt="">
            <div class="chip">
                <p>현재 보유칩</p>
                <b>145c</b>
            </div>
        </div>

        <hr class="hr">

        <!-- 칩 구매 버튼 -->
        <div class="buyBar">
            <p>온칩 <b>1</b>개</p>
            <button>300원</button>
        </div>

        <hr>

        <div class="buyBar">
            <p>온칩 <b>3</b>개</p>
            <button>900원</button>
        </div>

        <hr>

        <div class="buyBar">
            <p>온칩 <b>5</b>개</p>
            <button>1,500원</button>
        </div>

        <hr>

        <div class="buyBar">
            <p>온칩 <b>10</b>개</p>
            <button>3,000원</button>
        </div>

        <hr>

        <div class="buyBar">
            <p>온칩 <b>30</b>개</p>
            <button>9,000원</button>
        </div>

        <hr>

        <div class="buyBar">
            <p>온칩 <b>50</b>개</p>
            <button>15,000원</button>
        </div>

        <hr class="hr">
    </div>
</body>

</html>
)=====";

const char Information[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>회원정보</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <STYLe>
        *{
    margin: 0;
    padding: 0;
}
a{
    text-decoration: none;
    color: black;
}
body{
    background-color: rgb(244, 244, 244);
}
.div{
    background-color: rgb(244, 244, 244);
    display: flex;
    flex-direction: column;
}

/* 마이페이지 */
.mypage{
    padding-bottom: 10px;
    background-color: white;
    align-items: baseline;
    justify-content: flex-start;
    text-align: center;
}
.mypage > a > i{
    float: left;
    margin: 37px 0 0 37px;
}
h4{
    font-size: 20px;
    padding: 32px 37px 0 0;
}

/* 수정 창 */
form{
    /* width: 100%; */
    margin: 0 auto;
}
input:focus{
    outline:none;
}
.box{
    margin: 20px 0;
}
.box > small{
    font-size: 12px;
    float: left;
    color: black;
}
.box > input{
    width: 304px;
    height: 45px;
    font-size: 15px;
    padding-left: 5px;
    color: black;
    border: 0px;
    border-bottom: 1px solid rgba(174, 174, 174, 1);
    background-color: transparent;
}
.box > input::placeholder{
    color: rgba(190, 190, 190, 1);
    font-size: 15px;
}
.withdrawal{
    font-size: 12px;
    color: #828282;
    margin-bottom: 30px;
}
.withdrawal > button{
    font-size: 12px;
    border: none;
    background-color: rgb(244, 244, 244);
    color: #828282;
    padding-left: 90px;
}
.submit{
    width: 100%;
    border-radius: 8px;
    background-color: black;
    color: white;
    padding: 10px 0;
    align-items: center;
}
    </STYLe>
</head>
<body>
    <div class="div">
        <!-- 제목 -->
        <div class="mypage">
            <a href="./MyPage"><i class="fa-solid fa-angle-left"></i></a>
            <h4>회원정보수정</h4>
        </div>

        <form action="./MyPage" method="get">
            <div class="box">
                <small>이름</small>
                <br>
                <input type="text" maxlength="5" placeholder="이름을 입력해주세요." required>
            </div>
            
            <div class="box">
                <small>휴대폰 번호</small>
                <br>
                <input type="tel" maxlength="15" placeholder="휴대폰 번호를 입력해주세요." required>
            </div>

            <div class="box">
                <small>주소</small>
                <br>
                <input type="text" maxlength="40" placeholder="주소을 입력해주세요." required>
            </div>

            <div class="box">
                <small>환불계좌</small>
                <br>
                <input type="text" maxlength="40" placeholder="ex) 홍길동 (길동뱅크 0000-0000-0000-0)" required>
            </div>

            <div class="withdrawal">
                <span>회원 정보를 삭제하시겠어요 ?</span>
                <button>회원 탈퇴</button>
            </div>

            <input class="submit" type="submit" value="저장">
        </form>
    </div>
</body>
</html>
)=====";

const char Login[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>회원정보</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <STYLe>
        *{
    margin: 0;
    padding: 0;
}
a{
    text-decoration: none;
    color: black;
}
body{
    background-color: rgb(244, 244, 244);
}
.div{
    background-color: rgb(244, 244, 244);
    display: flex;
    flex-direction: column;
}

/* 마이페이지 */
.mypage{
    padding-bottom: 10px;
    background-color: white;
    align-items: baseline;
    justify-content: flex-start;
    text-align: center;
}
.mypage > a > i{
    float: left;
    margin: 37px 0 0 37px;
}
h4{
    font-size: 20px;
    padding: 32px 37px 0 0;
}

/* 수정 창 */
form{
    /* width: 100%; */
    margin: 0 auto;
}
input:focus{
    outline:none;
}
.box{
    margin: 20px 0;
}
.box > small{
    font-size: 12px;
    float: left;
    color: black;
}
.box > input{
    width: 304px;
    height: 45px;
    font-size: 15px;
    padding-left: 5px;
    color: black;
    border: 0px;
    border-bottom: 1px solid rgba(174, 174, 174, 1);
    background-color: transparent;
}
.box > input::placeholder{
    color: rgba(190, 190, 190, 1);
    font-size: 15px;
}
.withdrawal{
    font-size: 12px;
    color: #828282;
    margin-bottom: 30px;
}
.withdrawal > button{
    font-size: 12px;
    border: none;
    background-color: rgb(244, 244, 244);
    color: #828282;
    padding-left: 90px;
}
.submit{
    width: 100%;
    border-radius: 8px;
    background-color: black;
    color: white;
    padding: 10px 0;
    align-items: center;
}
    </STYLe>
</head>
<body>
    <div class="div">
        <!-- 제목 -->
        <div class="mypage">
            <a href="./MyPage"><i class="fa-solid fa-angle-left"></i></a>
            <h4>회원정보수정</h4>
        </div>

        <form action="./MyPage" method="get">
            <div class="box">
                <small>이름</small>
                <br>
                <input type="text" maxlength="5" placeholder="이름을 입력해주세요." required>
            </div>
            
            <div class="box">
                <small>휴대폰 번호</small>
                <br>
                <input type="tel" maxlength="15" placeholder="휴대폰 번호를 입력해주세요." required>
            </div>

            <div class="box">
                <small>주소</small>
                <br>
                <input type="text" maxlength="40" placeholder="주소을 입력해주세요." required>
            </div>

            <div class="box">
                <small>환불계좌</small>
                <br>
                <input type="text" maxlength="40" placeholder="ex) 홍길동 (길동뱅크 0000-0000-0000-0)" required>
            </div>

            <div class="withdrawal">
                <span>회원 정보를 삭제하시겠어요 ?</span>
                <button>회원 탈퇴</button>
            </div>

            <input class="submit" type="submit" value="저장">
        </form>
    </div>
</body>
</html>
)=====";

const char MyPage[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>mypage</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
      * {
  margin: 0;
  padding: 0;
}
a {
  text-decoration: none;
  color: black;
}
body {
  background-color: rgb(244, 244, 244);
}
.div {
  width: 100%;
}

/* 마이페이지 */
.mypage {
  background-color: white;
  align-items: baseline;
  justify-content: flex-start;
  text-align: center;
}
.mypage > a > i {
  float: left;
  margin: 37px 0 0 37px;
}
h4 {
  font-size: 20px;
  padding: 32px 37px 0 0;
}
.section {
  padding-bottom: 20px;
  margin: 60px 32px 15px 30px;
}

/* 문구, 칩 */
.flex-box {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.flex-box > p {
  font-size: 20px;
  font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
}
.flex-box > a {
  width: 64px;
  height: 30px;
  border-radius: 25px;
  border: 1px solid rgba(218, 218, 218, 1);
  font-size: 12px;
  background-color: white;
  text-align: center;
  line-height: 2.5;
}
button {
  width: 64px;
  height: 30px;
  border-radius: 25px;
  border: 1px solid rgba(218, 218, 218, 1);
  font-size: 12px;
  background-color: white;
}
.section > hr {
  margin: 16px 0 18px 0;
  border: 0px;
  border-bottom: 1px solid rgba(224, 224, 224, 1);
}
small {
  font-size: 16px;
  color: rgba(68, 68, 68, 1);
}
b {
  color: #ff2121;
  font-size: 40px;
}

/* 각종기능 */
#option {
  padding-top: 5px;
  padding: 5px 30px 6px 30px;
}
.box {
  margin: 22px 0;
}
.box > img {
  float: left;
}
.box > a {
  font-size: 17px;
  margin-left: 34px;
}
.inbox {
  display: flex;
  align-items: center;
  position: relative;
}
.wkdthdgk {
  display: flex;
}
.wkdthdgk > img {
  margin-right: 34px;
}

/* 가로줄 */
#option > hr {
  margin: 16px 0 18px 0;
  border: 0px;
  border-bottom: 1px solid rgba(224, 224, 224, 1);
}

/* on / off 버튼 */
.switch {
  position: absolute;
  width: 29px;
  height: 17px;
  right: 0;
  float: right;
}
.slider {
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  transition: 0.4s;
  border-radius: 34px;
}
.switch > input {
  display: none;
}
.slider::before {
  position: absolute;
  content: "";
  width: 15px;
  height: 15px;
  left: 1.3px;
  bottom: 1px;
  background-color: white;
  transition: 0.4s;
  border-radius: 50px;
}
input:checked + .slider {
  background-color: #fa5252;
}
input:checked + .slider::before {
  transform: translateX(12px);
}

/* 알림창 */
#alert-bg {
  position: absolute;
  z-index: 999;

  width: 100%;
  min-height: 118%;
  background-color: rgba(0, 0, 0, 0.5);
}
.close {
  display: none;
}
#alert {
  width: 250px;
  height: 130px;
  background-color: white;
  text-align: center;
  border-radius: 10px;
  border: 1px solid lightgray;
  padding-top: 10px;
  position: absolute;
  top: 35%;
  left: 50%;
  margin-left: -125px;
}
.text-box {
  margin: 28px 0 10px 0;
  border-bottom: 1px solid #dadada;
}
.text-box > p {
  font-size: 15px;
  margin-top: 3px;
}
.text-box > .p {
  font-size: 11px;
  margin-bottom: 20px;
}
.a-text > a {
  width: 125px;
  height: 43px;
  color: black;
  margin: 0 45px;
  font-size: 15px;
}
.white {
  background-color: white;
}

    </style>
</head>
<body>
    <div class="div">

        <!-- 알림창 -->
        <div id="alert-bg" class="close">
            <div id="alert">
                <div class="text-box">
                    <p>알림을 정말로 끄시겠습니까?</p>
                    <p class="p">배출시간 알림을 받지 못합니다.</p>
                </div>
        
                <div class="a-text">
                    <a href="#" onclick="ValAleart(true)">예</a>
                    <a href="#" onclick="ValAleart(false)">아니요</a>
                </div>
            </div>
        </div>

        <div class="white">
            <!-- 제목 -->
            <div class="mypage">
                <a href="./"><i class="fa-solid fa-angle-left"></i></a>
                <h4>마이페이지</h4>
            </div>
    
            <!-- section -->
            <div class="section">
                <div class="flex-box">
                    <p>장송하님, 반가워요 :)</p>
                    <a href="./Information">회원정보</a>
                </div>
                
                <hr>
        
                <small>현재 보유 칩</small>
        
                <div class="flex-box">
                    <b>4C</b>
                    <a href="./Chip">충전하기</a>
                </div>
            </div>
        </div>

        <!-- 옵션 -->
        <div class="white" id="option">
            <div class="box">
                <img src="https://user-images.githubusercontent.com/108206338/191420204-da529865-6e45-4849-ad7c-d5ef6a81a22e.png" alt="아이콘">
                <a href="./PaymentDetails">구매내역</a>
            </div>
            
            <hr>
            
            <div class="box inbox">
                <div class="wkdthdgk">
                    <img style="width: 24px; height: 24px;" src="https://user-images.githubusercontent.com/108206338/191420584-1915f1f4-bc93-4697-9460-09cc18f5000c.png" alt="아이콘">
                    <a href="#">알림설정</a>
                </div>

                <!-- on / off 버튼 -->
                <label class="switch" onchange="ChangeAleart()   ">
                    <input type="checkbox" checked id="checkInput" >
                    <span href="#" class="slider"></span>
                </label>
            </div>

            <hr>

            <div class="box">
                <img style="width: 24px; height: 24px;" src="https://user-images.githubusercontent.com/108206338/191418032-e581914d-c138-4c27-ad2e-eaa4bfee13b1.png" alt="아이콘">
                <a href="#">설정</a>
            </div>

            <hr>

            <div class="box">
                <img style="width: 24px; height: 24px;" src="https://user-images.githubusercontent.com/108206338/191420239-e1f59894-1da5-48bd-8162-44c4a92414bd.png" alt="아이콘">
                <a href="#">로그아웃</a>
            </div>
        </div>
    </div>

    <script>
        let alertBg = document.getElementById('alert-bg');
        let input = document.getElementById('checkInput');
        let alertBox = document.getElementById('alert');
        let count = 0;

        function ChangeAleart(){
            if(count % 2 == 0){
                alertBg.classList.remove('close');
                alertBox.classList.remove('show');
            }
            count++;
        }

        function ValAleart(e){
            if(e === true){
                alertBg.classList.add('close');
            }else{
                alertBg.classList.add('close');
                input.checked = true;
                count --;
            }
        }
    </script>

    <style>
        * {
  margin: 0;
  padding: 0;
}
a {
  text-decoration: none;
  color: black;
}
body {
  background-color: rgb(244, 244, 244);
}
.div {
  width: 100%;
}

/* 마이페이지 */
.mypage {
  background-color: white;
  align-items: baseline;
  justify-content: flex-start;
  text-align: center;
}
.mypage > a > i {
  float: left;
  margin: 37px 0 0 37px;
}
h4 {
  font-size: 20px;
  padding: 32px 37px 0 0;
}
.section {
  padding-bottom: 20px;
  margin: 60px 32px 15px 30px;
}

/* 문구, 칩 */
.flex-box {
  display: flex;
  justify-content: space-between;
  align-items: center;
}
.flex-box > p {
  font-size: 20px;
  font-family: "Segoe UI", Tahoma, Geneva, Verdana, sans-serif;
}
.flex-box > a {
  width: 64px;
  height: 30px;
  border-radius: 25px;
  border: 1px solid rgba(218, 218, 218, 1);
  font-size: 12px;
  background-color: white;
  text-align: center;
  line-height: 2.5;
}
button {
  width: 64px;
  height: 30px;
  border-radius: 25px;
  border: 1px solid rgba(218, 218, 218, 1);
  font-size: 12px;
  background-color: white;
}
.section > hr {
  margin: 16px 0 18px 0;
  border: 0px;
  border-bottom: 1px solid rgba(224, 224, 224, 1);
}
small {
  font-size: 16px;
  color: rgba(68, 68, 68, 1);
}
b {
  color: #ff2121;
  font-size: 40px;
}

/* 각종기능 */
#option {
  padding-top: 5px;
  padding: 5px 30px 6px 30px;
}
.box {
  margin: 22px 0;
}
.box > img {
  float: left;
}
.box > a {
  font-size: 17px;
  margin-left: 34px;
}
.inbox {
  display: flex;
  align-items: center;
  position: relative;
}
.wkdthdgk {
  display: flex;
}
.wkdthdgk > img {
  margin-right: 34px;
}

/* 가로줄 */
#option > hr {
  margin: 16px 0 18px 0;
  border: 0px;
  border-bottom: 1px solid rgba(224, 224, 224, 1);
}

/* on / off 버튼 */
.switch {
  position: absolute;
  width: 29px;
  height: 17px;
  right: 0;
  float: right;
}
.slider {
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  transition: 0.4s;
  border-radius: 34px;
}
.switch > input {
  display: none;
}
.slider::before {
  position: absolute;
  content: "";
  width: 15px;
  height: 15px;
  left: 1.3px;
  bottom: 1px;
  background-color: white;
  transition: 0.4s;
  border-radius: 50px;
}
input:checked + .slider {
  background-color: #fa5252;
}
input:checked + .slider::before {
  transform: translateX(12px);
}

/* 알림창 */
#alert-bg {
  position: absolute;
  z-index: 999;

  width: 100%;
  min-height: 118%;
  background-color: rgba(0, 0, 0, 0.5);
}
.close {
  display: none;
}
#alert {
  width: 250px;
  height: 130px;
  background-color: white;
  text-align: center;
  border-radius: 10px;
  border: 1px solid lightgray;
  padding-top: 10px;
  position: absolute;
  top: 35%;
  left: 50%;
  margin-left: -125px;
}
.text-box {
  margin: 28px 0 10px 0;
  border-bottom: 1px solid #dadada;
}
.text-box > p {
  font-size: 15px;
  margin-top: 3px;
}
.text-box > .p {
  font-size: 11px;
  margin-bottom: 20px;
}
.a-text > a {
  width: 125px;
  height: 43px;
  color: black;
  margin: 0 45px;
  font-size: 15px;
}
.white {
  background-color: white;
}

    </style>
</body>
</html>
)=====";

const char PaymentDetails[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>구매내역</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
        *{
    margin: 0;
    padding: 0;
}
a{
    text-decoration: none;
    color: black;
}
/* .div{
    height: 756px;
} */
.z-index{
    width: 100%;
    position: fixed;
    text-align: center;
}
.zero{
    padding-top: 140px;
}
/* top */
.top{
    width: 100%;
    height: 24px;
    display: flex;
    justify-content: flex-end;
    align-items: center;
}
.top > i{
    padding: 0 6px;
    font-size: 13px;
}
.top > p{
    padding-right: 5px;
    font-size: 14px;
}

/* 마이페이지 */
.mypage{
    padding-bottom: 16px;
    border-bottom: 2px solid rgb(244, 244, 244);
    background-color: white;
}
.mypage > a > i{
    float: left;
    margin: 37px 0 0 37px;
}
h4{
    font-size: 20px;
    padding: 32px 37px 0 0;
}

/* 결제, 구매 내역 */
.breakdown{
    height: 39px;
    background-color: white;
    padding-top: 14px;
    margin-bottom: 28px;
}
.breakdown > a{
    width: 180px;
    height: 45px;
    font-size: 17px;
    padding: 0 54px;
}
#a{
    border-bottom: 3px solid #fa5252;
    padding-bottom: 14px;
}

/* 내역 */
.div-box{
    padding-bottom: 30px;
    background-color: rgb(244, 244, 244);
}
.onchip{
    padding: 5px 24px;
    text-align: left;
    background-color: rgb(244, 244, 244);
}
.onchip > p{
    font-size: 12px;
    margin: 0 0 13px 10px;
}
.coin{
    background-color: white;
    padding: 11px 15px 11px 7px;
    display: flex;
    align-items: center;
    justify-content: space-around;
}
.coin-img{
    width: 35px;
    height: 35px;
    margin-right: 9px;
}
.text-box > small{
    font-size: 11px;
    color: #b9b9b9;
    margin-left: 2px;
}
.onchip-text{
    font-size: 15px;
}
.onchip-text-1{
    font-size: 15px;
    margin-left: 145px;
}
    </style>
</head>
<body>
    <div class="div">
        <div class="z-index">
            <!-- 제목 -->
            <div class="mypage">
                <a href="./MyPage"><i class="fa-solid fa-angle-left"></i></a>
                <h4>구매내역</h4>
            </div>

            <div class="breakdown">
                <a class="breakdown-a" id="a" href="./PaymentDetails">결제내역</a>
                <a class="breakdown-a" href="./UsageDetails">사용내역</a>
            </div>
        </div>

        <div class="div-box">
            <div class="onchip">
                <p class="zero">7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
    
            <div class="onchip">
                <p>7월 19일</p>
                <div class="coin">
                    <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                    <div class="text-box">
                        <p class="onchip-text">온칩 3개</p>
                        <small>01:27</small>
                    </div>
                    <p class="onchip-text-1">900원</p>
                </div>
            </div>
        </div>
    </div>
</body>
</html>
)=====";

const char UsageDetails[] PROGMEM =R"=====(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>사용내역</title>
    <script src="https://kit.fontawesome.com/2d62f67ec1.js" crossorigin="anonymous"></script>
    <style>
        *{
    margin: 0;
    padding: 0;
}
a{
    text-decoration: none;
    color: black;
}
.div{
    height: 756px;
    background-color: rgb(244, 244, 244);
}
.z-index{
    width: 100%;
    position: fixed;
    text-align: center;
}
.zero{
    padding-top: 140px;
}

/* top */
.top{
    width: 100%;
    height: 24px;
    display: flex;
    justify-content: flex-end;
    align-items: center;
}
.top > i{
    padding: 0 6px;
    font-size: 13px;
}
.top > p{
    padding-right: 5px;
    font-size: 14px;
}

/* 마이페이지 */
.mypage{
    padding-bottom: 16px;
    border-bottom: 2px solid rgb(244, 244, 244);
    background-color: white;
}
.mypage > a > i{
    float: left;
    margin: 37px 0 0 37px;
}
h4{
    font-size: 20px;
    padding: 32px 37px 0 0;
    /* text-align: center; */
}

/* 결제, 구매 내역 */
.breakdown{
    height: 39px;
    background-color: white;
    padding-top: 14px;
    margin-bottom: 28px;
}
.breakdown > a{
    width: 180px;
    height: 45px;
    font-size: 17px;
    padding: 0 54px;
}
#a{
    border-bottom: 3px solid #fa5252;
    padding-bottom: 14px;
}

/* 내역 */
.onchip{
    padding: 5px 24px 30px 24px;
    text-align: left;
    background-color: rgb(244, 244, 244);
}
.onchip > p{
    font-size: 12px;
    margin: 0 0 13px 10px;
}
.coin{
    background-color: white;
    padding: 11px 15px 11px 7px;
    display: flex;
    align-items: center;
    justify-content: space-around;
    margin-bottom: 9px;
}
.coin-img{
    width: 35px;
    height: 35px;
    margin-right: 9px;
}
.text-box > small{
    font-size: 11px;
    color: #b9b9b9;
    margin-left: 2px;
}
.onchip-text{
    font-size: 15px;
}
.onchip-text-1{
    font-size: 15px;
    margin-left: 175px;
    color: #066AFF;
}
.text-box-2 > small{
    font-size: 11px;
    margin-left: 175px;
    color: #B9B9B9;
}
.onchip-text-2{
    font-size: 15px;
    margin-left: 175px;
    color: #ff2020;
}
    </style>
</head>
<body>
    <div class="div">
        <div class="z-index">
            <!-- 제목 -->
            <div class="mypage">
                <a href="./MyPage"><i class="fa-solid fa-angle-left"></i></a>
                <h4>구매내역</h4>
            </div>

            <div class="breakdown">
                <a class="breakdown-a" href="./PaymentDetails">결제내역</a>
                <a class="breakdown-a" id="a" href="./UsageDetails">사용내역</a>
            </div>
        </div>

        <div class="onchip">
            <p class="zero">7월 19일</p>
            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>02:13</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-1">-1개</p>
                    <small>144개</small>
                </div>
            </div>

            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>01:27</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-2">+3개</p>
                    <small>145개</small>
                </div>
            </div>
        </div>
        <div class="onchip">
            <p>7월 19일</p>
            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>02:13</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-1">-1개</p>
                    <small>144개</small>
                </div>
            </div>

            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>01:27</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-2">+3개</p>
                    <small>145개</small>
                </div>
            </div>
        </div>
        <div class="onchip">
            <p>7월 19일</p>
            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>02:13</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-1">-1개</p>
                    <small>144개</small>
                </div>
            </div>

            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p>온칩</p>
                    <small>01:27</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-2">+3개</p>
                    <small>145개</small>
                </div>
            </div>
        </div>
        <div class="onchip">
            <p>7월 19일</p>
            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>02:13</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-1">-1개</p>
                    <small>144개</small>
                </div>
            </div>

            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p>온칩</p>
                    <small>01:27</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-2">+3개</p>
                    <small>145개</small>
                </div>
            </div>
        </div>
        <div class="onchip">
            <p>7월 19일</p>
            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p class="onchip-text">온칩</p>
                    <small>02:13</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-1">-1개</p>
                    <small>144개</small>
                </div>
            </div>

            <div class="coin">
                <img class="coin-img" src="https://user-images.githubusercontent.com/108206338/191418321-4aca948d-424d-413b-9bca-6365e0d6f12f.png" alt="">
                <div class="text-box">
                    <p>온칩</p>
                    <small>01:27</small>
                </div>
                <div class="text-box-2">
                    <p class="onchip-text-2">+3개</p>
                    <small>145개</small>
                </div>
            </div>
        </div>
        
    </div>
</body>
</html>
)=====";

ESP8266WebServer server(80);

void handleMain() {
  String html = Main;
  server.send(200, "text/html", html);
}

void handleIndex() {
  servo.write(25);
  String html = Index;
  server.send(200, "text/html", html);
}

void handleUnlock() {
  servo.write(170);
  String html = Unlock;
  server.send(200, "text/html", html);
}

void handleManagement() {
  String html = Management;
  server.send(200, "text/html", html);
}

void handleChip() {
  String html = Chip;
  server.send(200, "text/html", html);
}

void handleInformation() {
  String html = Information;
  server.send(200, "text/html", html);
}

void handleLogin() {
  String html = Login;
  server.send(200, "text/html", html);
}

void handleMyPage() {
  String html = MyPage;
  server.send(200, "text/html", html);
}

void handlePaymentDetails() {
  String html = PaymentDetails;
  server.send(200, "text/html", html);
}

void handleUsageDetails() {
  String html = UsageDetails;
  server.send(200, "text/html", html);
}
void setup()
{
  servo.attach(D4);
  servo.write(0);
  servo.write(92);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pw);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleMain);
  server.on("/Index", handleIndex);
  server.on("/Unlock", handleUnlock);
  server.on("/Management", handleManagement);
  server.on("/Chip", handleChip);
  server.on("/Information", handleInformation);
  server.on("/Login", handleLogin);
  server.on("/MyPage", handleMyPage);
  server.on("/PaymentDetails", handlePaymentDetails);
  server.on("/UsageDetails", handleUsageDetails);

  server.begin();
  Serial.println("Server started");
}
void loop(){
  server.handleClient();
}
