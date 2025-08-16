const
 maxn=100;
 fin='task.in'; fou='task.out';
type
 table=record
        s:array[0..maxn] of integer;
        len:integer;
       end;
 board=array[1..maxn,1..maxn] of integer;
 hp=record
     s:array[1..1000] of longint;
     len:integer;
    end;
 chesstype=record
            s:array[1..20] of record x,y:integer; end;
            len:integer;
           end;
var
 chessboard,Now:board;
 chess:chesstype;
 use:array[1..maxn,1..maxn] of boolean;
 n:integer;
 per,ans,Ri,one:table;

Procedure chessmul(a,b:table; var c:table);
var i,j:integer;
begin
 fillchar(c,sizeof(c),0);
 for i:=0 to a.len do
  for j:=0 to b.len do
   inc(c.s[i+j],a.s[i]*b.s[j]);
 c.len:=a.len+b.len;
end;

Procedure chessplus(a,b:table; var c:table);
var i,len:integer;
begin
 fillchar(c,sizeof(c),0);
 if a.len>b.len then len:=a.len else len:=b.len;
 for i:=0 to len do
   c.s[i]:=a.s[i]+b.s[i];
 c.len:=len;
end;

Procedure getinfo;
var i,j:integer;
begin
 assign(input,fin); reset(input);
 readln(n); fillchar(chessboard,sizeof(chessboard),0);
 for i:=1 to n do
  begin
   while not seekeoln do
    begin
     read(j);
     chessboard[i,j]:=1;
    end;
   readln;
  end;
 close(input);
end;

Procedure DFS(x,y:integer);
var i:integer;
begin
 use[x,y]:=false; Now[x,y]:=1;
 inc(chess.len);
 chess.s[chess.len].x:=x;
 chess.s[chess.len].y:=y;
 for i:=1 to x-1 do if (chessboard[i,y]=1)and(use[i,y]) then DFS(i,y);
 for i:=x+1 to n do if (chessboard[i,y]=1)and(use[i,y]) then DFS(i,y);
 for i:=1 to y-1 do if (chessboard[x,i]=1)and(use[x,i]) then DFS(x,i);
 for i:=y+1 to n do if (chessboard[x,i]=1)and(use[x,i]) then DFS(x,i);
end;

Procedure Work(chess:chesstype; var Ri:table);
var
 i,j,k,l:integer;
 a:table;

begin
 fillchar(ri,sizeof(ri),0);
 if chess.len=1 then
  begin
   Ri.len:=1;
   Ri.s[0]:=1; Ri.s[1]:=1;
   exit;
  end;
 if chess.len=0 then
  begin
   Ri.len:=0;
   Ri.s[0]:=1;
   exit;
  end;
 i:=chess.s[1].x;
 j:=chess.s[1].y;
 for k:=2 to chess.len do chess.s[k-1]:=chess.s[k];
 dec(chess.len);
 work(chess,a); chessplus(Ri,a,Ri);
 l:=0;
 for k:=1 to chess.len do
 if (chess.s[k].x<>i)and(chess.s[k].y<>j) then
  begin
   inc(l);
   chess.s[l]:=chess.s[k];
  end;
 chess.len:=l;
 work(chess,a);
 chessmul(a,per,a);
 chessplus(a,Ri,Ri);
end;

Procedure Solve;
var i,j,k,l:integer;
begin
 fillchar(use,sizeof(use),true);
 fillchar(per,sizeof(per),0);
 per.len:=1; per.s[1]:=1;
 fillchar(one,sizeof(one),0);
 one.s[0]:=1; ans:=one;
 for i:=1 to n do
  for j:=1 to n do if (use[i,j])and(chessboard[i,j]=1) then
   begin
    fillchar(Now,sizeof(Now),0);
    fillchar(chess,sizeof(chess),0);
    DFS(i,j);
    fillchar(Ri,sizeof(Ri),0);
    Work(chess,Ri);
    chessmul(ans,Ri,ans);
   end;
end;

Procedure mul(a:hp; k:integer; var b:hp);
var i:integer;
begin
 fillchar(b,sizeof(b),0);
 b.s[1]:=a.s[1]*k;
 for i:=2 to a.len do
  begin
   b.s[i]:=a.s[i]*k+b.s[i-1] div 10;
   b.s[i-1]:=b.s[i-1] mod 10;
  end;
 b.len:=a.len;
 while b.s[b.len]>9 do
  begin
   inc(b.len);
   b.s[b.len]:=b.s[b.len-1] div 10;
   b.s[b.len-1]:=b.s[b.len-1] mod 10;
  end;
end;

Procedure plus(a,b:hp; var c:hp);
var i,l:integer;
begin
 if a.len>b.len then l:=a.len else l:=b.len;
 fillchar(c,sizeof(c),0);
 c.s[1]:=a.s[1]+b.s[1];
 for i:=2 to l do
  begin
   c.s[i]:=a.s[i]+b.s[i]+c.s[i-1] div 10;
   c.s[i-1]:=c.s[i-1] mod 10;
  end;
 while c.s[l]>9 do
  begin
   inc(l);
   c.s[l]:=c.s[l-1] div 10;
   c.s[l-1]:=c.s[l-1] mod 10;
  end;
 c.len:=l;
end;

Procedure sub(a,b:hp; var c:hp);
var i,l:integer;
begin
 fillchar(c,sizeof(c),0);
 if a.len>b.len then l:=a.len else l:=b.len;
 for i:=1 to l do
  begin
   inc(c.s[i],a.s[i]-b.s[i]);
   if c.s[i]<0 then begin c.s[i]:=c.s[i]+10; dec(c.s[i+1]); end;
  end;
 while (l>1)and(c.s[l]=0) do dec(l);
 c.len:=l;
end;

Procedure jie(k:integer; var answer:hp);
var i:integer;
begin
 fillchar(answer,sizeof(answer),0);
 answer.s[1]:=1; answer.len:=1;
 for i:=2 to k do mul(answer,i,answer);
end;

Procedure getanswer;
var
 i:integer;
 answer,now:hp;
begin
 assign(output,fou); rewrite(output);
 jie(n,answer);
 for i:=1 to ans.len do
 if not odd(i) then
  begin
   jie(n-i,now);
   mul(now,ans.s[i],now);
   plus(answer,now,answer);
  end;
 for i:=1 to ans.len do if odd(i) then
  begin
   jie(n-i,now);
   mul(now,ans.s[i],now);
   sub(answer,now,answer);
  end;
 for i:=answer.len downto 1 do write(answer.s[i]);
 writeln;
 close(output);
end;

begin
 getinfo;
 Solve;
 getanswer;
end.
