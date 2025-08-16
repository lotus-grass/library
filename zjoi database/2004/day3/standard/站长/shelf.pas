var
 a:array[1..1000] of longint;
 use:array[1..1000] of boolean;
 i,n,min,ji,ou:longint;

Procedure DFS(k,ki:integer; od,even:boolean);
begin
 use[k]:=false;
 if use[a[k]]=false then
  begin
   if ki=1 then exit;
   min:=min+ki-1;
   if od and even then exit;
   if od then inc(ji) else inc(ou);
  end
 else DFS(a[k],ki+1,od or odd(a[k]),even or (not odd(a[k])));
end;

begin
 assign(input,'shelf.in'); reset(input);
 assign(output,'shelf.out'); rewrite(output);
 readln(n);
 for i:=1 to n do read(a[i]);
 ji:=0; ou:=0; min:=0;
 fillchar(use,sizeof(use),true);
 for i:=1 to n do if use[i] then DFS(i,1,odd(i),not odd(i));
 if ji>ou then min:=min+ji*2 else min:=min+ou*2;
 writeln(min);
 close(output); close(input);
end.
