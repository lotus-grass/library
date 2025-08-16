const inf='numfill.in';
      ouf='numfill.out';
var used,kk:array[1..1000] of boolean;
    pos:array[1..1000] of longint;
    n:longint;

procedure search(depth:longint);
var i:longint;
begin
     if depth>n then
     begin
          if not(used[abs(pos[n]-pos[1])]) then
          begin
               for i:=1 to n do
                 write(pos[i],' ');
               writeln;
          end;
          exit;
     end;
     for i:=1 to n+1 do
     if (not(kk[i])) and ((depth=1) or (not used[abs(i-pos[depth-1])]))then
     begin
          pos[depth]:=i;
          kk[i]:=true;
          if depth<>1 then used[abs(i-pos[depth-1])]:=true;
            search(depth+1);
          if depth<>1 then used[abs(i-pos[depth-1])]:=false;
          kk[i]:=false;
     end;
end;

begin
     assign(input,inf);
     reset(input);
     assign(output,ouf);
     rewrite(output);
        fillchar(pos,sizeof(pos),0);
        fillchar(used,sizeof(used),0);
        fillchar(kk,sizeof(kk),0);
       readln(n);
       search(1);
     close(input);
     close(output);
end.
