var
 D:array[1..100] of real;
 U,C:array[1..100] of longint;
 m,ans,save:real;
 s,n,i,j,now,max,last:longint;

Procedure Get(k,leave:longint);
var i:integer;
begin
 i:=k+1; ans:=ans+U[k]*D[k]; C[k]:=C[k]+U[k];
 if k=n then exit;
 while (i<=n)and(D[k]+m*(i-k)<D[i]) do
  begin
   if leave>=U[i] then
   begin
    dec(leave,U[i]); C[k]:=C[k]+U[i];
    C[i]:=0; ans:=ans+D[k]*U[i]+(i-k)*m*U[i];
    inc(i);
   end
   else
    begin
     U[i]:=U[i]-leave; C[k]:=C[k]+leave;
     ans:=ans+leave*(D[k]+(i-k)*m);
     Get(i,s);
     exit;
    end;
  end;
 if i<=n then Get(i,s);
end;

begin
 assign(input,'sell.in'); reset(input);
 assign(output,'sell.out'); rewrite(output);
 read(n); read(s); read(m);
 for i:=1 to n do read(D[i]);
 for i:=1 to n do read(U[i]);
 Get(1,s);
 writeln(ans:0:1);
 for i:=1 to n do write(C[i],' ');
 close(output); close(input);
end.
