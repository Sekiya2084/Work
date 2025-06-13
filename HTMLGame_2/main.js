//県情報
const prefecture = [
    ["札幌市","北海道","img/hokkaido.png","北海道の県庁所在地は札幌です","特産品はジンギスカン！"],
    ["盛岡市","岩手県","img/iwate.png","岩手県の県庁所在地は盛岡です","有名なのはわんこそば！"],
    ["仙台市","宮城県","img/miyagi.png","宮城県の県庁所在地は仙台です","有名なのは牛タン！"],
    ["水戸市","茨城県","img/ibaraki.png","茨城県の県庁所在地は水戸です","有名なのは納豆！"],
    ["宇都宮市","栃木県","img/tochigi.png","栃木県の県庁所在地は宇都宮です","有名なのは餃子！"],
    ["前橋市","群馬県","img/gunma.png","群馬県の県庁所在地は前橋です","有名なのは焼きまんじゅう！"],
    ["さいたま市","埼玉県","img/saitama.png","埼玉県の県庁所在地はさいたまです","有名なのは十万石まんじゅう！"],
    ["横浜市","神奈川県","img/kanagawa.png","神奈川県の県庁所在地は横浜です","有名なのは中華まんじゅう/シューマイ！"],
    ["甲府市","山梨県","img/yamanasi.png","山梨県の県庁所在地は甲府です","有名なのはほうとう！"],
    ["金沢市","石川県","img/isikawa.png","石川県の県庁所在地は金沢です","有名なのはきんつば！"],
    ["名古屋市","愛知県","img/aiti.png","愛知県の県庁所在地は名古屋です","有名なのはういろう！"],
    ["大津市","滋賀県","img/siga.png","滋賀県の県庁所在地は大津です","有名なのはじゅんじゅん！（すき焼き風の鍋料理）"],
    ["津市","三重県","img/mie.png","三重県の県庁所在地は津です","有名なのは赤福餅！"],
    ["神戸市","兵庫県","img/hyogo.png","兵庫県の県庁所在地は神戸です","有名なのは明石焼き！"],
    ["松江市","島根県","img/simane.png","島根県の県庁所在地は松江です","有名なのはどじょう掬い饅頭！"],
    ["高松市","香川県","img/kagawa.png","香川県の県庁所在地は高松です","有名なのは骨付鳥！"],
    ["松山市","愛媛県","img/ehime.png","愛媛県の県庁所在地は松山です","有名なのはじゃこ天うどん！"],
    ["那覇市","沖縄県","img/okinawa.png","沖縄県の県庁所在地は那覇です","有名なのはちんすこう！"]
]

//-------------------------------------------------------------------------------------------------------
// 変数
//-------------------------------------------------------------------------------------------------------

//問題数
var NumberOfQuestions = 3;
//時間制限
var Timelimit = 0;
//問題数計測
var AnsweredNum = 0;
//正解数計測
var CorrectNum = 0;
//ドロップ時比較用

var DuplicatePre = new Array;

var dropplace = 0;

var starttime;

var timesId;

var OldAnsNum;

//------------------------------------------------------------------------------------------------------

$(document).ready(function(){
    
    //各画面でのボタン処理
    //レベル1→時間制限なし3問
    //レベル2→時間制限20秒5問
    //レベル3→時間制限10秒10問
    //レベル4→時間制限5秒18問
    $("#js-easybutton>p").click(function(){
        gamelevel = 1;
        startgame();
    });
    $("#js-normalbutton>p").click(function(){
        gamelevel = 2;
        startgame();
    });
    $("#js-hardbutton>p").click(function(){
        gamelevel = 3;
        startgame();
    });
    $("#js-veryhardbutton>p").click(function(){
        gamelevel = 4;
        startgame();
    });
    $("#js-nextbutton>p").click(restartgame);
    $("#js-endbutton>p").click(endgame);
    $("#js-returnbutton>p").click(returntitle);
    $("#js-game").hide();
});


//配列からランダムに県情報を取得
function selectprefecture(){
    //直前の問題を取得して違う問題であれば出力
    OldAnsNum = AnsweredNum;
    var i = 0;
    var oldtemp = new Array;
    while(i < 3){
        random = Math.floor( Math.random() * prefecture.length );
        setbool = true;
        if(i == 0){
            for(l = 0; l < DuplicatePre.length; l++)
            {
                if(random != DuplicatePre[l]){
                    setbool = true;
                }
                else{
                    setbool = false;
                    break;
                }
            }
            if(setbool){
                oldtemp.unshift(random);
                DuplicatePre.unshift(random);
                $('#js-question').text(prefecture[oldtemp[0]][0]);
                i++;
            }
        }
        else{
            if(oldtemp[i - 1] != random){
                if(oldtemp[i - 2] != random){
                    oldtemp.unshift(random);
                    i++;
                }
            }
        }
    }

    j=0;
    var temp = new Array;
    while(j < 3){
        random2 = Math.floor( Math.random() * 3 );
        if(temp[j - 1] != random2){
            if(temp[j - 2] != random2){
                temp.unshift(random2);
                prefecturename = "prefecture" + (random2 + 1)
                document[prefecturename].src = prefecture[oldtemp[j]][2];
                document.getElementById(prefecturename).innerText = prefecture[oldtemp[j]][1];
                j++;
            }
        }
    }
};

//-------------------------------------------------------------------------------------------------------
// ドラッグアンドドロップ
//-------------------------------------------------------------------------------------------------------

//ドラッグ
$('#js-question').draggable({
    containment: "#js-game"
});

//ドロップ（正誤判定）
$('.js-prefecture').droppable({
    drop: function(e,ui) {
        $("#js-question").draggable("disable");
        var cityname;
        var Commentary;
        var CollectCommentary;
        i = 0;
        while (i < prefecture.length){
            if(prefecture[i][2] == $(this).attr("src")){
            cityname = prefecture[i][0];
            Commentary = prefecture[i][3];
            CollectCommentary = prefecture[i][4];
            break;
            }
            i++;
        }
        
        if(cityname == $("#js-question").text()) {
            $('#js-answertext').text("正解！！！");
            $('#js-answerimg').attr("src","img/maru.png");
            $('#js-columtext').text(CollectCommentary);
            $("#js-answer").show();
            AnsweredNum++;
            CorrectNum++;
            if(gamelevel > 1)
            clearTimeout(timesId);
        }

        else {
            $('#js-answertext').text("不正解……");
            $('#js-columtext').text(Commentary);
            $('#js-answerimg').attr("src","img/batu.png");
            $("#js-answer").show();
            AnsweredNum++;
            if(gamelevel > 1)
            clearTimeout(timesId);
        }
    }
});
//-------------------------------------------------------------------------------------------------------
// シーン遷移など
//-------------------------------------------------------------------------------------------------------

//ゲーム開始時処理
function startgame(){
    //シーンの切り替え
    $("#js-title").hide();
    $("#js-game").show();
    AnsweredNum = 0;
    CorrectNum = 0;
    //問題を初期化
    resetgame();
    //県情報の取得
    selectprefecture();
    //時間計測開始
    switch(gamelevel)
    {
        case 1:
        {
            $('#js-timer').text("");
            break;
        }
        case 2:
        {
            Timelimit = 20;
            NumberOfQuestions = 3;
            date = new Date();
            starttime = date.getTime();
            timemeasure();
            break;
        }
        case 3:
        {
            Timelimit = 10;
            NumberOfQuestions = 10;
            date = new Date();
            starttime = date.getTime();
            timemeasure();
            break;
        }
        case 4:
        {
            Timelimit = 5;
            NumberOfQuestions = 18;
            date = new Date();
            starttime = date.getTime();
            timemeasure();
            break;
        }
        default:
            break;
    }
}

//次に進む+一定数解答済みの場合リザルト遷移
function resetgame(){
    //移動したものを元に戻す（ドラッグを有効に戻す）
    $("#js-question").draggable("enable");
    $('#js-question').attr('style', 'top: 25%;','left: 40%;');
    //解答表示をリセット
    $("#js-answer").hide();
    //問題数分解答済みならリザルトへ遷移
    if(NumberOfQuestions == DuplicatePre.length){
        DuplicatePre = new Array();
    }
    if(NumberOfQuestions == AnsweredNum)
    {
        evaluation();
        endgame();
    }
}

//ゲームをリスタート
function restartgame(){
    resetgame();
    if(NumberOfQuestions != AnsweredNum){
        if(OldAnsNum == AnsweredNum)
            {
                date = new Date();
                starttime = date.getTime();
            }
            else{
                if(gamelevel > 1){
                    date = new Date();
                    starttime = date.getTime();
                    timemeasure();
                }
            }
        selectprefecture();
    }
}

//ゲーム終了時処理
function endgame(){
    //シーンの切り替え
    $("#js-game").hide();
    $("#js-result").show();
}

//タイトルへの遷移時処理
function returntitle(){
    //シーンの切り替え
    $("#js-result").hide();
    $("#js-title").show();
}

//-------------------------------------------------------------------------------------------------------
// ゲーム内部処理
//-------------------------------------------------------------------------------------------------------

//評価判定
function evaluation(){
    if(CorrectNum / AnsweredNum != 0)
        {
            $('#js-pointtext').html(CorrectNum + "/" + AnsweredNum + "問</br>"); 
            if(CorrectNum / AnsweredNum > 0.3){
                $('#js-resultimg').attr('src','img/bronze.png');
                $('#js-evaluationtext').text("ブロンズ級！");
            }
            if(CorrectNum / AnsweredNum > 0.6){
                $('#js-resultimg').attr('src',"img/silber.png");
                $('#js-evaluationtext').text("シルバー級！");
            }
            if(CorrectNum / AnsweredNum > 0.9){
                $('#js-resultimg').attr('src',"img/gold.png");
                $('#js-evaluationtext').text("ゴールド級！");
            }
        }
        else
        {
            $('#js-resultimg').attr('src',"img/white.png");
            $('#js-pointtext').css({'fontSize':'6vw'});
            $('#js-pointtext').html("もう一度</br>やってみよう！");
            $('#js-pagetitle').text("ざんねん！");
            $('#js-evaluationtext').text("");
        }
}

//時間処理
function timemeasure(){
    now = new Date();
    var finishtime = now.getTime();
    var remaining = finishtime - starttime;

    timer = Math.floor(remaining / 1000 % 60);
    timer = Timelimit - timer;
    $('#js-timer').text(timer);

    if(timer < 0){
        AnsweredNum++;
        restartgame();
    }

    timesId = setTimeout(() => {
        timemeasure();
    }, 500);
}