type arr=array[0..9]of int64;
var
  i:longint;
  a,b:int64;
  x,y:arr;
function calc(z:int64):arr;
  var tmp,e:int64;num:longint;
  begin
    fillchar(calc,sizeof(calc),0);
    if z=0 then exit;
    tmp:=z;num:=0;
    while tmp>9 do begin tmp:=tmp div 10;inc(num);end;
    e:=1;for i:=1 to num do e:=e*10;
    while e>0 do
      begin
        num:=z div e mod 10;
        tmp:=z div e div 10;
        for i:=0 to 9 do calc[i]:=calc[i]+tmp*e;
        if num=0 then calc[0]:=calc[0]-e;
        for i:=1 to num-1 do calc[i]:=calc[i]+e;
        calc[num]:=calc[num]+z mod e+1;
        e:=e div 10;
      end;
  end;
begin
  assign(input,'count.in');
  assign(output,'count.out');
  reset(input);
  rewrite(output);
  readln(a,b);
  x:=calc(a-1);y:=calc(b);
  for i:=0 to 8 do write(y[i]-x[i],' ');
  writeln(y[9]-x[9]);
  close(input);
  close(output);
end.
