<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
  <script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
  <link rel="stylesheet" href="./css/index.css">
  <script src="./javascript/index.js"></script>
</head>

<body>
<!-- header -->
<div class="container-fluid jumbotron">
<img style="float:left;height:125px;" src='./images/shield.jpeg'></img><center><p><h1>Water Shield</h1></p></center>
</div>
<!-- /header -->



<!-- side navigation bar -->
<div id="mySidenav" class="sidenav">
  <a href="javascript:void(0)" class="closebtn" onclick="closeNav()">&times;</a>
  <a href="#" onclick="home()">Home</a>
  <a href="#" onclick="node2()">Vazirabad</a>
  <a href="#" onclick="node3()">Anand-Nagar</a>
  <a href="#" onclick="node4()">Kabra Nagar</a>
</div>
<span style="font-size:30px;cursor:pointer" onclick="openNav()">&#9776; open</span>
<!-- /side navigation bar -->


<div>
<div  id='node1_line_graph' style="height: 400px; width: 90%; display:block"></div>

<br>
<br>
<br>

<div  id='node1_line_graph_turbidity'></div>

<div class='container' id='demo'><h2 id='node1_closed_turbidity'></h2> </div>

<div  id='node2_line_graph'></div>

<div  id='node2_line_graph_turbidity'></div>

</div>
</body>
</html> 
