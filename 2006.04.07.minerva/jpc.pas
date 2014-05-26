unit jpc;

interface
uses
  Sysutils, Windows;

procedure fin;
procedure code;
procedure assemble;
function construct(pszName : PChar): string;

implementation

var
 ax, bx,cx,dx,si,tmp,x1a2,res,i,inter,cfc,cfd,compte, c :  word;
 d,e : short;
 c1, t1, count : integer;
 x1a0 : array[0..16] of word;
 cle  : array[0..32] of char;
 buff : array[0..32] of char;
 buff2: array[0..255] of char;

 //- delphi implementation of the pukkal 256 bit cipher by j.b. gericke -----------------------

 procedure fin;
 var
  cCount : word;
 begin

 for cCount := 0 to 31 do
  begin
  ax := 0;
  bx := 0;
  cx := 0;
  dx := 0;
  si := 0;
  tmp := 0;
  x1a2 := 0;
  x1a0[0] := 0;
  x1a0[1] := 0;
  x1a0[2] := 0;
  x1a0[3] := 0;
  x1a0[4] := 0;
  res := 0;
  i := 0;
  inter := 0;
  cfc := 0;
  cfd := 0;
  compte := 0;
  c := 0;
  end;
 end;

//------------------------------------------------------------------------------

 procedure code;
  begin

   dx := x1a2+i;
   ax := x1a0[i];
   cx := $015a;
   bx := $4e35;

   tmp := ax;
   ax := si;
   si := tmp;

   tmp := ax;
   ax := dx;
   dx := tmp;

  if (ax <> 0) then
   begin
   ax := ax * bx;
   end;

    tmp := ax;
    ax := cx;
    cx := tmp;

   if (ax <> 0) then
    begin
     ax := ax*si;
     cx := ax+cx;
     end;

   tmp := ax;
   ax := si;
   si := tmp;
   ax := ax*bx;
   dx := cx+dx;
   ax := ax+1;
   x1a2 := dx;
   x1a0[i] := ax;
   res := ax xor dx;
   i := i+1;
 end;

//------------------------------------------------------------------------------

 procedure assemble;
 begin
  x1a0[0] := ( ord(cle[0])*256 )+ ord(cle[1]);
   code;
    inter := res;

  x1a0[1] := x1a0[0] xor ( (ord(cle[2])*256) + ord(cle[3]) );
   code;
    inter := inter xor res;

  x1a0[2] := x1a0[1] xor ( (ord(cle[4])*256) + ord(cle[5]) );
   code;
    inter := inter xor res;

  x1a0[3] := x1a0[2] xor ( (ord(cle[6])*256) + ord(cle[7]) );
   code;
    inter := inter xor res;

  x1a0[4] := x1a0[3] xor ( (ord(cle[8])*256) + ord(cle[9]) );
   code;
    inter := inter xor res;

  x1a0[5] := x1a0[4] xor ( (ord(cle[10])*256) + ord(cle[11]) );
   code;
    inter := inter xor res;

  x1a0[6] := x1a0[5] xor ( (ord(cle[12])*256) + ord(cle[13]) );
   code;
    inter := inter xor res;

  x1a0[7] := x1a0[6] xor ( (ord(cle[14])*256) + ord(cle[15]) );
   code;
    inter := inter xor res;

  x1a0[8] := x1a0[7] xor ( (ord(cle[16])*256) + ord(cle[17]) );
   code;
    inter := inter xor res;

  x1a0[9] := x1a0[8] xor ( (ord(cle[18])*256) + ord(cle[19]) );
   code;
    inter := inter xor res;

  x1a0[10] := x1a0[9] xor ( (ord(cle[20])*256) + ord(cle[21]) );
   code;
    inter := inter xor res;

  x1a0[11] := x1a0[10] xor ( (ord(cle[22])*256) + ord(cle[23]) );
   code;
    inter := inter xor res;

  x1a0[12] := x1a0[11] xor ( (ord(cle[24])*256) + ord(cle[25]) );
    code;
     inter := inter xor res;

  x1a0[13] := x1a0[12] xor ( (ord(cle[26])*256) + ord(cle[27]) );
    code;
     inter := inter xor res;

  x1a0[14] := x1a0[13] xor ( (ord(cle[28])*256) + ord(cle[29]) );
    code;
     inter := inter xor res;

  x1a0[15] := x1a0[14] xor ( (ord(cle[30])*256) + ord(cle[31]) );
    code;
     inter := inter xor res;

  i := 0;
 end;

//------------------------------------------------------------------------------

 function construct(pszName : PChar): string;
 var
 x,ix,z,fin1 : word;
 tab : array[0..32] of char;
 j : integer;
 Begin

    x := 32;
    si := 0;
    x1a2 := 0;
    i := 0;

    StrCopy(cle,'abcdefghijklmnopqrstuvwxyz012345');  // padding
    StrCopy(buff,pszName);


    if strlen(buff)>32 then
    begin
     count := 32;
    end else begin
     count := strlen(buff);
    end;

    for c1 :=0 to count do
    begin
     cle[c1] := buff[c1];
    end;

    ix := 0;

    for z := 0 to x do
    begin
     tab[z] := ' ';
    end;

    for c1 := 0 to 32 do
    begin
     c := ord(cle[c1]);
     assemble;
     cfc := inter shr 8;
     cfd := inter and 255;

    for compte := 0 to 31 do
    begin
     cle[compte] := Char(ord(cle[compte]) xor c);
    end;

    c := c xor (cfc xor cfd);

    tab[ix] := Char(ord(tab[ix]) xor c);

    ix := ix + 1;

    if ix >= x then
    begin
     ix := 0;
    end;
    end;

    fin1 := 63254;

    for z := 1 to fin1 do
    begin
     c := ord(tab[ix]);
     assemble;
     cfc := inter shr 8;
     cfd := inter and 255;

    for compte :=0 to 31 do
    begin
     cle[compte] := Char(ord(cle[compte]) xor c);
    end;

    c := c xor (cfc xor cfd);
    tab[ix] := Char(ord(tab[ix]) xor c);
    ix := ix + 1;

    if ix >= x then
    begin
     ix := 0;
    end;
    end;

    t1 := 0;

    for z :=0 to x do
    begin
     d :=( ord(tab[z]) shr 4);
     e :=( ord(tab[z]) and 15);
     buff2[t1] := Char(d + $61);
     buff2[t1+1] := Char(e + $61);
     t1 := t1+2;
    end;

    for j := 0 to strlen(buff2) do
    begin
     Result := Result + buff2[j];
    end;
    fin();

 end;


end.
