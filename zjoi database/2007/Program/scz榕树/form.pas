const maxn=500000;

type ptype=^ppp;
     ppp=record
           da:longint;
           next:ptype;
         end;
     treetype=^ttt;
     ttt=record
           da,h:longint;
           l,r:treetype;
         end;

var n,m,i,j,k,no:longint;
    min1,min2:longint;
    a,b:array[1..maxn]of ptype;
    head:treetype;
    p:ptype;

procedure readstring;
var ch:char;
    i:longint;
begin
     read(ch);
     if ch='I' then
     begin
       for i:=1 to 5 do read(ch);
       no:=0;
     end
     else
     begin
       for i:=1 to 6 do read(ch);
       if ch='P' then no:=1
       else no:=2;
       readln;
     end;
end;

function height(t:treetype):longint;
begin
     if t=nil then exit(0)
     else exit(t^.h);
end;

function max(x,y:longint):longint;
begin
     if x>y then exit(x)
     else exit(y)
end;

function single_l(t:treetype):treetype;
var temp:treetype;
begin
     temp:=t^.l;
     t^.l:=t^.l^.r;
     t^.h:=max(height(t^.l),height(t^.r))+1;
     temp^.r:=t;
     temp^.h:=max(height(t^.l),height(t^.r))+1;
     exit(temp);
end;

function single_r(t:treetype):treetype;
var temp:treetype;
begin
     temp:=t^.r;
     t^.r:=t^.r^.l;
     t^.h:=max(height(t^.l),height(t^.r))+1;
     temp^.l:=t;
     temp^.h:=max(height(t^.l),height(t^.r))+1;
     exit(temp);
end;

function double_l(t:treetype):treetype;
begin
     t^.l:=single_r(t^.l);
     double_l:=single_l(t);
end;

function double_r(t:treetype):treetype;
begin
     t^.r:=single_l(t^.r);
     double_r:=single_r(t);
end;

function insert(t:treetype;da:longint):treetype;
begin
     if t=nil then
     begin
       new(t);
       t^.l:=nil;
       t^.r:=nil;
       t^.da:=da;
       t^.h:=1;
     end
     else
     if t^.da=da then min2:=0
     else
     begin
       if abs(t^.da-da)<min2 then min2:=abs(t^.da-da);
       if t^.da>da then
       begin
         t^.l:=insert(t^.l,da);
         if height(t^.l)-height(t^.r)>1 then
         if height(t^.l^.l)>=height(t^.l^.r) then t:=single_l(t)
         else t:=double_l(t)
       end
       else
       begin
         t^.r:=insert(t^.r,da);
         if height(t^.r)-height(t^.l)>1 then
         if height(t^.r^.r)>=height(t^.r^.l) then t:=single_r(t)
         else t:=double_r(t);
       end;
     end;
     exit(t);
end;

begin
     assign(input,'form.in');
     reset(input);
     assign(output,'form.out');
     rewrite(output);
     readln(n,m);
     head:=nil;
     min1:=maxlongint;
     min2:=maxlongint;
     for i:=1 to n do
     begin
       new(p);
       p^.next:=nil;
       read(p^.da);
       a[i]:=p;
       b[i]:=p;
       if i>1 then if abs(p^.da-a[i-1]^.da)<min1 then min1:=abs(p^.da-a[i-1]^.da);
       head:=insert(head,p^.da);
     end;
     readln;

     for i:=1 to m do
     begin
       readstring;
       case no of
       0:begin
           readln(j,k);
           if abs(k-b[j]^.da)<min1 then min1:=abs(k-b[j]^.da);
           if j<n then if (k-a[j+1]^.da)<min1 then min1:=abs(k-a[j+1]^.da);
           new(p);
           p^.da:=k;
           p^.next:=nil;
           b[j]^.next:=p;
           b[j]:=p;
           head:=insert(head,k);
         end;
       1:writeln(min1);
       2:writeln(min2);
       end;
     end;
     close(input);
     close(output);
end.
