<?xml version="1.0" encoding="utf-8" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml-transitional.dtd" >
<html>
 <head>
  <title>progtest.fit.cvut.cz - ProgTest</title>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
  <link href="/css.css" rel="stylesheet" type="text/css" />
  <script src="/shared.js" language="JavaScript" type="text/javascript"></script>
 </head>
 <body bgcolor="#928293" text="#000000">
 

  <script language="JavaScript" type="text/javascript">
  <!--
  var g_Shibboleth = new Array ();
  function doValidate ( )
   {
     var P1 = MM_findObj ( 'USERNAME' );

     if ( P1.value == "" )
      {
        alert ( 'Chybí uživatelské jméno' );
        return ( false );
      }
     return ( 1 );
   }
  function changeLg ( x )
   {
     var url = x . options[x . selectedIndex ] . value;
     document . location = url;
   }
  function visibleById ( id, show )
   {
     var x = MM_findObj ( id );
     if ( !x ) return;
     x . style . visibility = show;
   }
  function addShib ( uid )
   {
     g_Shibboleth[ uid ] = 1;
   }
  function changeUni ( )
   {
     var x = MM_findObj ( 'UID_UNIVERSITY' );
     var uni = x . options[x . selectedIndex] . value;
     var tbl = MM_findObj ( 'main' );

     for ( i = 1; i <= 3; i ++ )
      {
        visibleById ( 'ldap' + i, g_Shibboleth [ uni ] ? 'collapse' : 'visible' );
        visibleById ( 'shib' + i, g_Shibboleth [ uni ] ? 'visible' : 'collapse' );
      }
     if ( ! g_Shibboleth [ uni ] )
      {
        x = MM_findObj ( "USERNAME" );
        x . focus ();
      }
   }
  // -->
  </script>

  <br />
  <br />
  <form name="form" method="post" action="?X=Login&amp;UID=749&amp;N=1&amp;Lg=1" onsubmit="return( doValidate () )">
   <center>
    <div class="insBox">
     <div class="outBox">
      <table width="100%" border="0" cellspacing="0" cellpadding="0" align="center" id="main">
       <col width="50%" />
       <col width="50%" />
       <tbody>
        <tr>
         <td class="lrtbCell" colspan="2"><select class="std fw" name="lang" onchange="changeLg(this)"><option value="?X=ImgT&amp;UID=749&amp;N=1&amp;Lg=1" selected="selected" >CZE</option><option value="?X=ImgT&amp;UID=749&amp;N=1&amp;Lg=2" >ENG</option></select></td>
        </tr>
        <tr>
         <td class="al ltbCell"><b>Škola</b></td>
         <td class="rtbCell"><select class="std w200" name="UID_UNIVERSITY" onchange="changeUni()"><option value="2S" selected="selected">ČVUT - FIT</option><option value="2">ČVUT - FIT (bez shibboleth)</option><option value="3">Akademie Silicon Hill</option><option value="6">Ostatní</option><option value="1">ČVUT - FEL</option><option value="4">VŠB - FEI</option><option value="5">Tecnológico de Monterrey</option></select></td>
        </tr>

        <tr id="shib1" style="visibility: collapse">
         <td class="lrtCell ac" colspan="2">
           <img src="shibboleth.png" width="200" />
         </td>
        </tr>
        <tr id="shib2" style="visibility: collapse">
         <td class="lrbCell ac" colspan="2">Přihlášení pomocí služby Shibboleth (jednotné heslo ČVUT)</td>
        </tr>
        <tr id="shib3" style="visibility: collapse">
         <td class="Cell" colspan="2" align="center">
          <div class="but1 w120"><div class="but2"><a class="butLink" href="shibboleth-fit.php">Login</a></div></div>
         </td>
        </tr>

        <tr id="ldap1">
         <td class="ltCell al"><b>Username</b></td>
         <td class="rtCell"><input class="std w200" name="USERNAME" /></td>
        </tr>
        <tr id="ldap2">
         <td class="al lbCell"><b>Heslo</b></td>
         <td class="rbCell"><input type="password" class="std w200" name="PASSWORD" /></td>
        </tr>
        <tr id="ldap3">
         <td class="Cell" colspan="2" align="center">
          <table border="0">
           <tr>
            <td><div class="outButton w120"><input type="submit" class="updButton" name="Login" value="Login" /></div></td>
            <td><div class="outButton w120"><input type="submit" class="updButton" name="LoginMail" value="Poslat heslo" /></div></td>
           </tr>
          </table>
         </td>
        </tr>
       </tbody>
      </table>
     </div>
    </div>
   </center>
  </form>
  <script language="JavaScript" type="text/javascript">
  <!--
   addShib('2S');

   changeUni ();

   document . onkeydown = function ( e )
    {
      if ( e . altKey && e . which >= 49 && e . which <= 57 )
       {
         var x = document . getElementsByName ( 'UID_UNIVERSITY' )[0];
         var choice = e . which - 49;
         if ( choice < x . options . length )
          {
            x . selectedIndex = e . which - 49;
            changeUni ();
          }
         return false;
       }
      return true;
    }
  // -->
  </script>


 </body>
</html>
<!-- Template run time: 0.0025279521942139 sec -->
