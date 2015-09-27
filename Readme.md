#MultiCameraViewer
複数のカメラ画像を表示するRTC

##開発環境
- MacOSX Yosemite
- openrtm-aist 1.1 (c++)
- c++11
- OpenCV 2.4

##使い方

### ダウンロード

    git clone https://github.com/cormoran/RTC_MultiCameraViewer.git

### コンパイル



    cd RTC_MultiCameraViewer
    mkdir build
    cd build
    cmake ..
    make



RTC_MultiCameraViewer/build/src/ 以下のどこかに実行ファイルができる

### 実行後

    画像を表示するWindowがアクティブな状態で

    q : 終了

    A : 画像ポート追加（今はコンポーネントが追加される）


##Todo
- Windowsで動くようにする
- Ubuntuで動くようにする
- 今はコンポーネントを増やしているが、ポートを増やすように変更する
- 画像を減らせるようにする
