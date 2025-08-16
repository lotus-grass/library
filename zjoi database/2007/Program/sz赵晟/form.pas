const inf='form.in';
      ouf='form.out';
      maxn=500000;

type p=^node;
     node=record
        le,ri,fa:p;
        tot,be,en:longint;
          end;

var pre,inp:array[1..maxn] of longint;
    n,m,len,mina,minb:longint;
    head:p;

procedure setup;
begin
     assign(input,inf);
     reset(input);
     assign(output,ouf);
     rewrite(output);
end;

procedure endit;
begin
     close(input);
     close(output);
end;

function findmore(x:p;n:longint):longint;
var a:longint;
begin
     if (x^.be=x^.en) then
     begin
          if (x^.be=n) then if (x^.tot>1) then exit(n) else exit(-1);
          if (x^.be>n) and (x^.tot>0) then exit(x^.be);
          exit(-1);
     end;
     if (x^.en<n) then exit(-1);
     if (x^.tot=0) then exit(-1);
     a:=findmore(x^.le,n);
     if a=-1 then
        a:=findmore(x^.ri,n);
     exit(a);
end;

function findless(x:p;n:longint):longint;
var a:longint;
begin
     if (x^.be=x^.en) then
     begin
          if (x^.be=n) then if (x^.tot>1) then exit(n) else exit(-1);
          if (x^.be<n) and (x^.tot>0) then exit(x^.be);
          exit(-1);
     end;
     if (x^.be>n) then exit(-1);
     if (x^.tot=0) then exit(-1);
     a:=findless(x^.ri,n);
     if a=-1 then
        a:=findless(x^.le,n);
     exit(a);
end;

procedure insert(n:longint);
var x,t:p;
    a,b:longint;
begin
     x:=head;
     while x^.be<>x^.en do
     begin
          inc(x^.tot);
          if x^.le=nil then
          begin new(t);x^.le:=t;t^.tot:=0;t^.be:=x^.be;t^.en:=(x^.be+x^.en) div 2; end;
          if x^.ri=nil then
          begin new(t);x^.ri:=t;t^.tot:=0;t^.be:=(x^.be+x^.en) div 2+1;t^.en:=x^.en; end;
          if n<=(x^.be+x^.en) div 2 then x:=x^.le else x:=x^.ri;
     end;
     inc(x^.tot);
     x:=head;
     a:=findmore(head,n);
     if (a<>-1) and (abs(n-a)<minb) then minb:=abs(n-a);
     b:=findless(head,n);
     if (b<>-1) and (abs(n-b)<minb) then minb:=abs(n-b);
end;

function minx(a,b:longint):longint;
begin
    if a<b then exit(a) else exit(b);
end;

procedure work;
var i,j,a,b,p:longint;
    rea:string;
begin
     new(head);
     head^.fa:=nil;head^.tot:=0;head^.be:=0;head^.en:=800000000;
     len:=0;
     readln(n,m);
     minb:=maxlongint;
     for i:=1 to n do
     begin
       read(pre[i]);
       inp[i]:=pre[i];
       insert(pre[i]);
     end;readln;
     mina:=maxlongint;
     for i:=1 to n-1 do
         if mina>abs(pre[i]-pre[i+1]) then mina:=abs(pre[i]-pre[i+1]);
     for i:=1 to m do
     begin
          readln(rea);
          if rea='MIN_SORT_GAP' then begin writeln(minb);end else
          if rea='MIN_GAP' then begin writeln(mina);end else
          begin
               p:=8;a:=0;while (rea[p]<='9') and (rea[p]>='0') do begin a:=a*10+ord(rea[p])-48;inc(p) end;
               b:=0;inc(p);while (p<=length(rea)) do begin b:=b*10+ord(rea[p])-48;inc(p);end;
               if a<>n then mina:=minx(mina,abs(pre[a+1]-b));
               mina:=minx(mina,abs(inp[a]-b));
               inp[a]:=b;
               if minb<>0 then
               begin
                    insert(b);
               end;
          end;
     end;
end;

begin
     setup;
       work;
     endit;
end.
