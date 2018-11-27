//課題3 2610180082 水野響
#include <stdio.h>
#include <stdlib.h>
#include <glsc.h>

double dice();

int main(){
  double N;
  int j,r,t;
  int sum=0;
  double count[1000]={};
  double high[1000] = {};
  char text[256];
  char text2[256];
  srand(100);
  printf("サイコロの試行1000回*実験回数:");
  scanf("%lf",&N);
  //初期設定
  g_init("GRAPH", 240.0, 240.0);
  g_device(G_DISP);
  //仮想座標系の定義
  g_def_scale(1, 0.0, 1000.0, -40.0, 20.0, 20.0, 10.0, 200.0, 150.0);
  //入力された回数分1000回試行を繰り返す
  for(int i=0; i<N; i++){
    //サイコロを1000回振る
    for(int j=0;j<1000;j++){
      r = dice();
      count[j] = r;
    }
    //グラフの描画
    g_sel_scale(1);
    //軸ラベルの記述
    g_text(15,12,"20");
    g_text(17,62,"0");
    g_text(13,110,"-20");
    g_text(20,115,"0");
    g_text(115,115,"500");
    g_text(215,115,"1000");
    g_area_color(G_WHITE);
    g_line_color(G_BLACK);
    g_line_width(1);
    //箱
    g_box(0,1000, -20, 20, G_YES, G_YES);
    g_box(0,1000, -40, -35, G_YES, G_YES);
    //下のboxの区分け
    for(t=1;t<41;t++){
      g_move(t*25,-35);
      g_plot(t*25,-40);
    }
    //上のグラフの中央のライン
    g_move(0,0);
    g_plot(1000,0);

    //描画インデント
    for(int k=0;k<1000;k++){
      //でた目が1,2だと+1で,3,4だと-1.
      if(count[k]<2){
        if(k != 0){
          high[k] = high[k-1] + 1;
        }else{
          high[k] = 1;
        }
      }
      else if(count[k]<4){
        if(k != 0){
          high[k] = high[k-1] - 1;
        }else{
          high[k] = 1;
        }
      }
      //ランダムウォークを赤線で引く！
      g_line_color(G_RED);
      //x軸0からjまで配列highの値をj番目まで
      g_data_plot(0, k, high, k);

      //赤い丸でhighの値を可視化
      g_area_color(G_RED);
      g_circle(512+25*high[k],-37.5,10,G_YES,G_YES);
      g_sleep(0.01);
      //赤い円と文字をi番目の文字を一旦消す
      g_area_color(G_WHITE);
      g_line_color(G_WHITE);
      g_circle(512+25*high[k],-37.5,10,G_YES,G_YES);
      g_area_color(G_WHITE);
      g_box(0,50,-27,-30,G_YES,G_YES);
      //文字列表示. n次元, i番目
      sprintf(text, "n = %d", 1000);
      sprintf(text2,"i = %d", k+1);
      g_text(15.0, 125.0, text);
      g_text(15.0, 133.0, text2);
    }
    //配列|high|<=20より超えた値を|high|=20に制限.
    for(int k=0;k<1000;k++){
      if(high[k] <= -20){
        high[k] = -20;
      }
      else if(20 <= high[k]){
        high[k] = 20;
      }
    }
  }
  g_sleep(G_STOP);
  g_term();
  return 0;
}

//サイコロ関数 0~5までの値をランダムに返す.
double dice(){
  int r;
  double R;
  r = rand();
  R = (double)(r % 6);
  return (int)R;
}
