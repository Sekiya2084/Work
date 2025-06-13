//化石情報
const fossil = [
    ["img/anmonite.png","indexfossil","アンモナイト：示準化石（中生代）</br>中生代白亜紀末に絶滅するまで世界中の海で栄えた。</br>年代ごとに殻の形に特徴的な違いがみられるため、出現した古生代デボン紀から中生代白亜紀末まで地層の年代をはかる材料になる。","アンモナイト"],
    ["img/asari.png","phasefossil","アサリ：示相化石</br>生息環境からその地域が昔、浅い海だったことがわかる。","アサリ"],
    ["img/hotate.png","phasefossil","ホタテ：示相化石</br>生息環境からその地域が昔、寒冷な海であったことがわかる","ホタテ"],
    ["img/sijimi.png","phasefossil","シジミ：示相化石</br>生息環境からその地域が昔、淡水湖/汽水湖河口付近だったことがわかる。</br>（※淡水：塩分をほぼ含まない水、汽水：海水と淡水が混ざった水）","シジミ"],
    ["img/konoha.png","phasefossil","木の葉（ブナ）：示相化石</br>ブナの葉がとりあげられることが多く</br>その場合はその地域が昔、温帯のやや寒冷な地域だったことがわかる。","木の葉（ブナ）"],
    ["img/kyoryu.png","indexfossil","恐竜：示準化石（中生代）</br>恐竜は主に中生代に生きていたため、その地層が中生代に堆積したものだということがわかる。","恐竜"],
    ["img/manmos.png","","マンモス：示相・示準化石（新生代 第四紀）</br>実はどっちを選んでも正解。</br>示相化石としてはその地域が寒い気候であったことを示し、</br>示準化石としては新生代第四紀のころに堆積した地層であることがわかる","マンモス"],
    ["img/sango.png","phasefossil","サンゴ：示相化石</br>生息環境からその地域が昔、暖かくて浅い海だったことがわかる。","サンゴ"],
    ["img/sanyotyu.png","indexfossil","三葉虫：示準化石（古生代）</br>古生代ペルム紀末まで世界中の海で栄えた。</br>アンモナイトと同じく年代ごとに形が違っているため、出現したカンブリア紀からペルム紀末まで地層の年代をはかる材料になる","三葉虫"]
]

//-------------------------------------------------------------------------------------------------------
// 変数
//-------------------------------------------------------------------------------------------------------

//問題数
const NumberOfQuestions = 3;
//問題数計測
var AnsweredNum = 0;
//正解数計測
var CorrectNum = 0;
//ドロップ時比較用
var temp;

var oldtemp =  new Array;

//------------------------------------------------------------------------------------------------------

$(document).ready(function(){
    //各画面でのボタン処理
    $("#js-startbutton>p").click(startgame);
    $("#js-nextbutton>p").click(restartgame);
    $("#js-endbutton>p").click(endgame);
    $("#js-returnbutton>p").click(returntitle);
    $("#js-howtoplaybutton>p").click(howtoplay);
    $("#js-howtoreturn>p").click(howtoreturn);
    $("#js-howtolite>p").click(howtolite);
    
    $("#js-game").hide();
    $("#js-howtoplay").hide();
    $("#js-howtoplaylite").hide();
});

//配列からランダムに化石情報を取得
function selectfossil(){
    //直前の問題を取得して違う問題であれば出力
    var setbool = true;
    
    for(;;){
        var random = Math.floor( Math.random() * fossil.length );
        for(var i=0;i < oldtemp.length; i++){
            if(oldtemp[i] != random){
                setbool = true;
            }
            else{
                setbool = false;
                break;
            }
        }
    
        if(setbool){
            temp = random;
            oldtemp.unshift(random);
            $('#js-questiontext').text(fossil[random][3] + "はどっち！");
            $('#js-answercolum').html(fossil[random][2]);
            $('#js-question').attr("src",fossil[random][0]);
            break;
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
$('.fossilBox').droppable({
    drop: function(e,ui) {
        $("#js-question").draggable("disable");
        if(fossil[temp][3] == "マンモス"){
            $('#js-answertext').text("正解！！！");
            $('#js-answerimg').attr('src',"img/maru.png");
            $("#js-answer").show();
            AnsweredNum++;
            CorrectNum++;
        }
        else{
            if(fossil[temp][1] == $(this).attr("id")){
                $('#js-answertext').text("正解！！！");
                $('#js-answerimg').attr('src',"img/maru.png");
                $("#js-answer").show();
                AnsweredNum++;
                CorrectNum++;
            }
            else{
                $('#js-answertext').text("不正解……") ;
                $('#js-answerimg').attr('src',"img/batu.png");
                $("#js-answer").show();
                AnsweredNum++;
            }
        }
    }
});

//-------------------------------------------------------------------------------------------------------
// シーン遷移
//-------------------------------------------------------------------------------------------------------

//ゲーム開始時処理
function startgame(){
    //シーンの切り替え
    $("#js-title").hide();
    AnsweredNum = 0;
    CorrectNum = 0;
    oldtemp =  new Array;
    //問題を初期化
    resetgame();
    //化石情報の取得
    selectfossil();
    $("#js-game").show();
}

//問題の内容をリセット
function restartgame(){
    resetgame();
    if(oldtemp.length == fossil.length)
        {oldtemp =  new Array;}
    selectfossil();
}

//次に進む+一定数解答済みの場合リザルト遷移
function resetgame(){
    //移動したものを元に戻す（ドラッグを有効に戻す）
    $("#js-question").draggable("enable");
    $('#js-question').attr('style', 'top: 25%;','left: 40%;');
    //解答表示をリセット
    $("#js-answer").hide();
    //問題数分解答済みならリザルトへ遷移
    if(NumberOfQuestions == AnsweredNum)
    {
        $('#js-pagetitle').text("正答数！");
        if(CorrectNum / AnsweredNum != 0)
        {
            $('#js-pointtext').html(CorrectNum + "/" + AnsweredNum + "問</br>"); 
            if(CorrectNum / AnsweredNum > 0.3){
                $('#js-resultimg').attr('src',"img/bronze.png");
                $('#js-evaluationtext').text("ブロンズ級！");
            }
            if(CorrectNum / AnsweredNum > 0.6){
                $('#js-resultimg').attr('src',"img/silber.png");
                $('#js-evaluationtext').text("シルバー級！");
            }
            if(CorrectNum / AnsweredNum == 1){
                $('#js-resultimg').attr('src',"img/gold.png");
                $('#js-evaluationtext').text("ゴールド級！");
            }
        }
        else
        {
            $('#js-resultimg').attr("src","img/white.png");
            $('js-pointtext').css({"fontsize":"6vw"});
            $('#js-pointtext').html("もう一度</br>やってみよう！");
            $('#js-pagetitle').text("ざんねん！");
            $('#js-evaluationtext').text("");
        }
        endgame();
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

function howtoplay() {
    $("#js-howtoplay").show();
    setTimeout(function() {
        $("#js-howtocircle").hide();
        $("#js-howtotext").hide();
        $("#js-howtoquestion").addClass('howtoanimation');
        setTimeout(function() {
            $("#js-howtoresult").show();
            $("#js-howtocircle").css({
                'height':'7.5vw',
                'width':'7.5vw',
                'top':'69%',
                'right':'17.5%'
            });
            $("#js-howtotext").text("②解答で化石への理解を深め「次の問題へ」ボタンで次へ進む");
            $("#js-howtotext").css({
                'top' : '75%',
                'right': '27%',
                'height': 'auto'
            })
            $("#js-howtocircle").show();
            $("#js-howtotext").show();
        },1500);
    }, 2000);
}

function howtoreturn(){
    $("#js-howtoplay").hide();
    $("#js-howtoplaylite").hide();
    $("#js-howtoresult").hide();
    $("#js-howtoquestion").removeClass('howtoanimation');
    $("#js-howtocircle").css({
        'height':'',
        'width':'',
        'top':'',
        'right':''
    });
    $("#js-howtotext").html("①画像をあっていると思うほうに</br>引っ張っていく");
    $("#js-howtotext").css({
        'top' : '',
        'right': '',
        'height': ''
    })
}

function howtolite(){
    $("#js-howtoplay").hide();
    $("#js-howtoplaylite").show();
}


/* function howtoplayanim(){
    const element = document.getElementById('show')

    element.addEventListener('animationend', () => {
        // アニメーション終了後に実行する内容
        alert('animationend')
    })
} */