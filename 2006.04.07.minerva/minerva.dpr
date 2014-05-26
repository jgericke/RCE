program minerva;
 uses
  Windows,
  Messages,
  SysUtils,
  Sha1,
  Base64,
  FGint,
  FGIntRSA,
  jpc;
var
  x,y,w,h	:integer;
  wrec	:TRect;
  wClass	:TWndClass;
  hFont, hInst, Handle, hDesktop, hlblName, hlblReg,
  hedtCode, hedtName, hbtnReg, hbtnAbt	:HWND;
  Msg	:TMSG;
  dUno, nUno, dDuo, nDuo, k1, k2 : TFGInt;

 procedure ExitMinerva;
 begin
  DeleteObject(hFont);
  UnRegisterClass('minclass',hInst);
  ExitProcess(0);
 end;

//- Lame xor crypt -------------------------------------------------------------

 function lCx(s : string): string;
 var
  i : integer;
 Begin
   for i := 1 to Length(s) do
   begin
     s[i] := Char(10 * i div 10 xor ord(s[i]));
     Result := s;
   end;
 end;


//- Create large numbers -------------------------------------------------------


 function genNum(sHash : string; pOrQ : integer): string;
 var
  sPstr, sQstr : String;
  sD1, sD2, sD3, sD4 : String;
  c1, c2, c3, c4  : TSHA1Context;
  d1, d2, d3, d4  : TSHA1Digest;
  i : integer;
 Begin

   sHash := construct(PChar(sHash));

   SHA1Init(c1);
   SHA1Update(c1,@sHash[1],Length(sHash));
   SHA1Final(c1,d1);

   for i:= 0 to (Sizeof(d1)-1) do
   begin
      sD1 := sD1 + IntToHex(d1[i],2);
   end;

   SHA1Init(c2);
   SHA1Update(c2,@sD1[1],Length(sD1));
   SHA1Final(c2,d2);

   for i:= 0 to (Sizeof(d2)-1) do
   begin
      sD2 := sD2 + IntToHex(d2[i],2);
   end;

   SHA1Init(c3);
   SHA1Update(c3,@sD2[1],Length(sD2));
   SHA1Final(c3,d3);

   for i:= 0 to (Sizeof(d3)-1) do
   begin
      sD3 := sD3 + IntToHex(d3[i],2);
   end;

   SHA1Init(c4);
   SHA1Update(c4,@sD3[1],Length(sD3));
   SHA1Final(c4,d4);

   for i:= 0 to (Sizeof(d4)-1) do
   begin
      sD4 := sD4 + IntToHex(d4[i],2);
   end;

   sPstr := sD1 + sD2 + sD3 + sD4;

   i := length(sPstr);

   while i <> 0 do
   begin
     sQstr := sQstr + sPstr[i];
     i := i - 1;
   end;

   if(pOrQ = 1) then Result := sPstr else Result := sQstr;

end;


//- Generate primes ------------------------------------------------------------

 function genPQ(pTest : TFGInt): TFGInt;
 var
  pInc : TFGInt;
  primeFlag : boolean;
  i : integer;
 Begin
   i := 0;
   FGIntPrimetest(pTest, 1, primeFlag);
   while (primeFlag <> true) do
   begin
      i := i + 1;
      Base10StringToFGInt(inttostr(i), pInc);
      FGIntAdd(pInc, pTest, pTest);
      FGIntPrimetest(pTest, 1, primeFlag);
   end;
   Result := pTest;
   FGIntDestroy(pTest);
   FGIntDestroy(pInc);
 end;


//- RSA gen1 -------------------------------------------------------------------


 procedure genUno(sNameHash : string);
 var
  sGenP, sGenQ, sPstr, sQstr  : string;
  e, n, d : TFGInt;
  q, p, dp, dq, one, two, phi, gcd, temp, nilgint : TFGInt;
  x1, y1 : TFGInt;
 begin

   sGenP := genNum(sNameHash, 1);
   sGenQ := genNum(sNameHash, 2);

   ConvertHexStringToBase256String( sGenP, sPstr );
   ConvertHexStringToBase256String( sGenQ, sQstr );
   Base256StringToFGInt( sPstr, p );
   Base256StringToFGInt( sQstr, q );
   Base10StringToFGInt('65537', e);
   Base10StringToFGInt('1', one);
   Base10StringToFGInt('2', two);
   p := genPQ(p);
   q := genPQ(q);

    //-------------------------------\\
      // y = g(two) ^ x(p) % n(q)
      FGIntModExp(two, p, q, y1);
      // x = g(two) ^ y(q) % n(p)
      FGIntModExp(two, q, p, x1);
      //k1 = y^x % n(q)
      FGIntModExp(y1, x1, q, k1);
      //k2 = x^y % n(p)
      FGIntModExp(x1, y1, p, k2);
   //--------------------------------\\

   FGIntMul( p, q, n );
   p.Number[1] := p.Number[1] - 1;
   q.Number[1] := q.Number[1] - 1;
   FGIntMul( p, q, phi );

   FGIntGCD( phi, e, gcd );
   While FGIntCompareAbs( gcd, one ) <> Eq do begin
     FGIntAdd( e, two, temp );
     FGIntCopy( temp, e );
     FGIntGCD( phi, e, gcd );
   end;

   FGIntDestroy( two );
   FGIntDestroy( one );
   FGIntDestroy( gcd );

   FGIntModInv( e, phi, d );
   FGIntModInv( e, p, dp );
   FGIntModInv( e, q, dq );
   p.Number[1] := p.Number[1] + 1;
   q.Number[1] := q.Number[1] + 1;

   FGIntDestroy(phi);
   FGIntDestroy(nilgint);
   FGIntDestroy( e );

   dUno := d;
   nUno := n;

   FGIntDestroy( n );
   FGIntDestroy( d );
   FGIntDestroy( q );
   FGIntDestroy( p );
   FGIntDestroy( y1 );
   FGIntDestroy( x1 );
   FGIntDestroy( dp );
   FGIntDestroy( dq );
   FGIntDestroy( phi );
   FGIntDestroy( temp );

 end;

//- RSA gen2 -------------------------------------------------------------------

 procedure genDuo();
 var
  e, n, d : TFGInt;
  q, p, dp, dq, one, two, phi, gcd, temp, nilgint : TFGInt;
 begin

   p := k1;
   q := k2;
   Base10StringToFGInt('65539', e);
   Base10StringToFGInt('1', one);
   Base10StringToFGInt('2', two);
   p := genPQ(p);
   q := genPQ(q);

   FGIntMul( p, q, n );
   p.Number[1] := p.Number[1] - 1;
   q.Number[1] := q.Number[1] - 1;
   FGIntMul( p, q, phi );

   FGIntGCD( phi, e, gcd );
   While FGIntCompareAbs( gcd, one ) <> Eq do begin
     FGIntAdd( e, two, temp );
     FGIntCopy( temp, e );
     FGIntGCD( phi, e, gcd );
   end;

   FGIntDestroy( two );
   FGIntDestroy( one );
   FGIntDestroy( gcd );

   FGIntModInv( e, phi, d );
   FGIntModInv( e, p, dp );
   FGIntModInv( e, q, dq );
   p.Number[1] := p.Number[1] + 1;
   q.Number[1] := q.Number[1] + 1;

   FGIntDestroy( phi );
   FGIntDestroy( nilgint );
   FGIntDestroy( e );

   dDuo := d;
   nDuo := n;

   FGIntDestroy( n );
   FGIntDestroy( d );
   FGIntDestroy( q );
   FGIntDestroy( p );
   FGIntDestroy( dp );
   FGIntDestroy( dq );
   FGIntDestroy( phi );
   FGIntDestroy( temp );

 end;


//------------------------------------------------------------------------------

 procedure cReg;
 var
  nLen : integer;
  uName, uCode : PChar;
  sNameHash, sSession, sEncode, sFHash : String;
  nilgint : TFGInt;
  hWindow : HWND;
 begin

//- Get Name + Code + Hash of Name ---------------------------------------------

   GetMem(uName,100);
   nLen := GetWindowText(hedtName, uName, 20);
   if nLen < 4 then
   begin
     SetWindowText(hedtCode,PChar(lCx('Dlwaw&f(gkfi-i}upfvf5byw:/<~v~RR')));
     FreeMem(uName);
     Exit;
   end;

   GetMem(uCode,2048);
   GetWindowText(hedtCode, uCode, 1024);
   sSession := uCode;
   FreeMem(uCode);
   sNameHash := construct(uName);
   FreeMem(uName);

//- Get Name + Code + Hash of Name ---------------------------------------------

   genUno(sNameHash);
   genDuo;

   sEncode := '';
   sSession := B64Decode(sSession);

//------------------------------------------------------------------------------

   RSADecrypt( sSession, dDuo, nDuo, nilgint, nilgint, nilgint, nilgint, sEncode );
   sEncode := B64Decode(sEncode);
   RSADecrypt( sEncode, dUno, nUno, nilgint, nilgint, nilgint, nilgint, sFHash );
   sFHash := B64Decode(sFHash);

   if (StrLComp(PChar(sFHash), PChar(sNameHash), 66) = 0) then
   Begin
       MessageBox(hWindow,PChar(lCx('Ujbp%ot(jey~hm{1')),PChar(lCx('Sgdmvrbzln)')),MB_OK OR MB_APPLMODAL) end
   Else
       MessageBox(hWindow,PChar(lCx('Ujbp%ot(`dhc|jse')),PChar(lCx('Tlqabot|lxnh)')),MB_OK OR MB_APPLMODAL);

   FGIntDestroy( nilgint );
   FGIntDestroy( k1 );
   FGIntDestroy( k2 );
   FGIntDestroy( dDuo );
   FGIntDestroy( dUno );
   FGIntDestroy( nDuo );
   FGIntDestroy( nUno );

//------------------------------------------------------------------------------

end;

// Window stuff below

 function WindowProc(hWnd,Msg,wParam,lParam:Longint):Longint; stdcall;
 begin
  Result:=DefWindowProc(hWnd,Msg,wParam,lParam);
  case Msg of
  WM_COMMAND: if lParam=Longint(hbtnReg) then cReg else if lParam=Longint(hbtnAbt) then
              MessageBox(hWnd,'.:: Minerva ::.'#13#10#13#10'A crackme by [_j_]'#10#13#10,'About...',
              MB_ICONINFORMATION OR MB_OK OR MB_APPLMODAL);
  WM_DESTROY: ExitMinerva;
  end;
 end;

 begin
  hInst:=GetModuleHandle(nil);
  with wClass do
  begin
    Style:=         CS_HREDRAW or CS_VREDRAW;
    hIcon:=         LoadIcon(hInst,'MAINICON');
    lpfnWndProc:=   @WindowProc;
    hInstance:=     hInst;
    hbrBackground:= COLOR_BTNFACE+1;
    lpszClassName:= 'minclass';
    hCursor:=       LoadCursor(0,IDC_ARROW);
  end;

  RegisterClass(wClass);
  h:=GetSystemMetrics(SM_CYSIZE);
  h:=(h-18)+210;
  w:=395;
  hDesktop:=GetDesktopWindow();
  GetWindowRect(hDesktop,wrec);
  x:=wrec.right;
  y:=wrec.bottom;
  x:=(x-365) div 2;
  y:=(y-h) div 2;

  Handle:=CreateWindowEx(WS_EX_DLGMODALFRAME, 'minclass',
  'MiNERVA',
  WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX or WS_VISIBLE,
  x, y, w, h, 0, 0, hInst, nil);

  hbtnReg:=CreateWindowEx(0, 'Button', 'Register', WS_VISIBLE or WS_CHILD ,
  5,155,190,24,Handle,0,hInst,nil);

  hbtnAbt:=CreateWindowEx(0, 'Button', 'About', WS_VISIBLE or WS_CHILD ,
  195,155,190,24,Handle,0,hInst,nil);

  hFont:=CreateFont(-12, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
    DEFAULT_QUALITY, DEFAULT_PITCH or FF_DONTCARE, 'Arial');

  hedtName:=CreateWindowEx(WS_EX_CLIENTEDGE,'Edit','',
  WS_VISIBLE or WS_CHILD or ES_LEFT or ES_AUTOHSCROLL,
  5,20,380,20,Handle,0,hInst,nil);

  hedtCode:=CreateWindowEx(WS_EX_CLIENTEDGE,'Edit','',
  WS_VISIBLE or WS_CHILD or WS_VSCROLL or ES_MULTILINE,
  5,65,380,85,Handle,0,hInst,nil);

  hlblName:=CreateWindowEx(0, 'Static', 'Name:', WS_VISIBLE or WS_CHILD or SS_LEFT,
  5,2,40,18,Handle,0,hInst,nil);

  hlblReg:= CreateWindowEx(0, 'Static', 'Registration Code:', WS_VISIBLE or WS_CHILD or SS_LEFT,
  5,45,105,18,Handle,0,hInst,nil);

    SendMessage(hedtCode,WM_SETFONT,hFont,0);
    SendMessage(hedtCode,EM_SETLIMITTEXT, 4096, 0);
    SendMessage(hedtName,WM_SETFONT,hFont,0);
    SendMessage(hedtName,EM_SETLIMITTEXT,20,0);
    SendMessage(hbtnReg,WM_SETFONT,hFont,0);
    SendMessage(hbtnAbt,WM_SETFONT,hFont,0);
    SendMessage(hlblName,WM_SETFONT,hFont,0);
    SendMessage(hlblReg,WM_SETFONT,hFont,0);

    SetFocus(hedtName);
  while(GetMessage(Msg,Handle,0,0))do
  begin
    TranslateMessage(Msg);
    DispatchMessage(Msg);
  end;

end.
