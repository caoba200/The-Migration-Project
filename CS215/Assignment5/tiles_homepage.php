<?php session_start();

	//Get username and profile picture
	$uname = $_SESSION["username"];
	$image = $_SESSION["image"];

?>
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml">
    <head>
	    <meta charset="utf-8"/>
        <title>Tiles</title>    
        <link rel="stylesheet" type="text/css" href="style.css">
        <script type="text/javascript" src="button_handler.js"></script>
    </head>
    <body>
        <header>
            <div class="headerlogo">
              <table>
                  <td><a href="tiles_homepage.php"><img src="logo.png" alt="logo" align="middle"/></a></td>
                    <td><h1>Home Page</h1></td>
                </table>
            </div>
        </header>
        <aside>
            <article>
                <a href="tiles_userinfo.php"><img href="<?=$image?>" alt="placeholder"/></a>
                <strong>Daniel B. Knights</strong><br/>
                <a href="tiles_userinfo.php">@sampleusername</a>
                <hr/>
                <div class="asidebutton">
                    <p>Want to share something?</p>
                    
                    <form action="postreposthandle.php" method="post">
                        <button type="submit" name="newpost">NEW POST</button>
                    </form>
                    
                </div>
                <div class="asidebutton">
                    <p>Log out?</p>
                    <a href="logout.php"><button>LOG OUT</button></a>
                </div>
                <div class="asidebutton">
                    <p>Log in to a different name?</p>
                    <a href="logout.php"><button>LOG IN</button></a>
                </div>
            </article>
        </aside>
        
        <!-*************** USER SAMPLE NUMBER 1 ************->
        <section class="homepage">
            <div class="sectionheader">
                <div class="headeruserinfo">
                    <a href="tiles_userinfo.php"><img src="profile_picture2.jpg" alt="pp"/></a>
                </div>
                <div class="headeruserinfo">
                    <strong>Bruce Wayne</strong><br/>
                    <a href="tiles_userinfo.php">@iambatman</a>
                </div>
                
                <p>February 5, 2018 -- 10 minutes ago</p>
            </div>
            <article class="sectionbody">
                <p>Lorem Ipsum é simplesmente uma simulação de texto da indústria tipográfica e de impressos, e vem sendo utilizado desde o século XVI, quando um impressor desconhecido pegou uma bandeja de tipos e os embaralhou para fazer um livro de modelos de tipos. Lorem Ipsum sobreviveu não só a cinco séculos, como também ao salto para a editoração eletrônica, permanecendo essencialmente inalterado. Se popularizou na década de 60, quando a Letraset lançou decalques access the link <a href="http://www2.cs.uregina.ca/~caoba200/" target="_blank">http://www2.cs.uregina.ca/~caoba200/</a> quando passou a ser integrado a softwares de editoração eletrônica como Aldus PageMaker.
                </p>
            </article>
            <div class="sectionfooter">
                
                <div class="footerbuttonposition"><button>LIKE</button>&nbsp;<strong>12</strong></div>
                <div class="footerbuttonposition"><button>DISLIKE</button>&nbsp;<strong>32</strong></div>
                <div class="footerbuttonposition"><button>REPOST</button>&nbsp;<strong>7</strong></div>
            </div>
        </section>
        
        <!-*************** USER SAMPLE NUMBER 2 ************->
        <section class="homepage">
            <div class="sectionheader">
                <div class="headeruserinfo">
                    <a href="tiles_userinfo.php"><img src="profile_picture3.jpg" alt="pp"/></a>
                </div>
                <div class="headeruserinfo">
                    <strong>Trooper</strong><br/>
                    <a href="tiles_userinfo.php">@starwarfan</a>
                </div>
                <p>February 14, 2078 -- 60 years from now</p>
            </div>
            <article class="sectionbody">
                <p>Lorem Ipsum é simplesmente uma simulação de texto da having fun with <a href="tiles_userinfo.php" target="_blank">@iambatman</a> e de impressos, e vem sendo utilizado desde o século XVI, quando pegou uma bandeja de tipos e os embaralhou para fazer um livro de modelos de tipos. Lorem Ipsum sobreviveu não só a cinco séculos, como também ao salto para a editoração eletrônica, permanecendo essencialmente inalterado. Se popularizou na década de 60, quando a Letraset lançou decalques contendo passagens de Lorem Ipsum, e mais recentemente quando passou a ser integrado a softwares de editoração eletrônica como Aldus PageMaker.
                </p>
            </article>
            <div class="sectionfooter">
                
                <div class="footerbuttonposition"><button>LIKE</button>&nbsp;<strong>12</strong></div>
                <div class="footerbuttonposition"><button>DISLIKE</button>&nbsp;<strong>32</strong></div>
                <div class="footerbuttonposition"><button>REPOST</button>&nbsp;<strong>7</strong></div>
            </div>
        </section>
        
        <!-*************** USER SAMPLE NUMBER 3 ************->
        <section class="homepage">
            <div class="sectionheader">
                <div class="headeruserinfo">
                    <a href="tiles_userinfo.php"><img src="profile_picture4.png" alt="pp"/></a>
                </div>
                <div class="headeruserinfo">
                    <strong>Deadpool</strong><br/>
                    <a href="tiles_userinfo.html">@friendlyneighbor</a>
                </div>
                <p>January 1, 2017 -- It's hard to calculate</p>
            </div>
            <article class="sectionbody">
                <p>This is a post from my friend Daniel B. Knights</p>
                <p>------Post from <a href="tiles_userinfo.php" target="_blank">@sampleusername</a>-------</p>
                <p>Lorem Ipsum é simplesmente uma simulação de texto da having fun with <a href="tiles_userinfo.php" target="_blank">@iambatman</a> e de impressos, e vem sendo utilizado desde o século XVI, quando pegou uma bandeja de tipos e os embaralhou para fazer um livro de modelos de tipos. Lorem Ipsum sobreviveu não só a cinco séculos, como também ao salto para a editoração eletrônica, permanecendo essencialmente inalterado. Se popularizou na década de 60, quando a Letraset lançou decalques contendo passagens de Lorem Ipsum, e mais recentemente quando passou a ser integrado a softwares de editoração eletrônica como Aldus PageMaker.
                </p>
            </article>
            <div class="sectionfooter">
                
                <div class="footerbuttonposition"><button>LIKE</button>&nbsp;<strong>12</strong></div>
                <div class="footerbuttonposition"><button>DISLIKE</button>&nbsp;<strong>32</strong></div>
                <div class="footerbuttonposition"><button>REPOST</button>&nbsp;<strong>7</strong></div>
            </div>
        </section>
        <script type="text/javascript" src="button_events.js"></script>
        
        <!------------------------ PHP ---------------------------------->
    </body>
</html>