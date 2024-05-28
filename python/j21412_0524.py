import random
from msvcrt import getch

f = open(r"C:\Users\81802\Desktop\main\hotsuen_home\J4\big_theme\toeic1500_utf.dat","r",encoding="utf-8")
word = []
japanese = []


#ファイル読み込み
a = 0
for line in f:
    word.append(line.split(' ')[1])
    japanese.append(line.split(' ')[2])
    
    a += 1


mode = 0
while  mode == 0:
    #0~最大行数-1の範囲からランダムな数値を生成
    num = random.randint(0,a-1)
    
    #初期化
    text = japanese[num-1].replace('\n','')
    answer = ['-'] * len(word[num-1])
    question = list(word[num-1])
    use = []
    
    game = 0
    count = 7
    while game == 0:
        
        #プレイヤーに入力を求める
        while True:
            print('意味：%s' % (text))
            print('単語：',end = '')
            for i in answer:
                print(i,end = '')
            print()
            print('使われた文字：',end = '')
            for i in use:
                print(i,end = '')
            print()
            print('残り回数：',count)
            print('英子文字を入力してください：',end = '')
            s = getch()
            input = chr(s[0])
            print(input)
            print()
            
            #一度入力した文字ではないかチェック
            x = 0
            for i in use:
                if input == i:
                    input = '0'
                    print('一度入力しています')
                    print()
                    
                x += 1
            
            if input != '0' and 'a'<=input and input <= 'z':
                use.append(input)
                
            if 'a'<=input and input <= 'z':
                break
            
        #一致したかチェック
        check = 0
        x = 0
        for i in word[num-1]:
            if input == i:
                answer[x] = i
                check += 1
            x += 1
        
        if check == 0:
            count -= 1
        
        
        #クリア判定
        if answer == question:
            print('ゲームクリア！')
            print('答え：',word[num-1])
            game += 1
        elif count == 0:
            print('ゲームオーバー')
            print('答え：',word[num-1])
            game += 1
    
    #ゲーム進行の確認
    while True:
        print('ゲームを続けますか？(y/n)：',end = '')
        s = getch()
        input = chr(s[0])
        print(input)
        if input == 'y':
            break
        elif input == 'n':
            mode += 1
            break

f.close