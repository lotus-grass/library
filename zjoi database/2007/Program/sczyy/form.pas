const maxr=500000000;
      maxn=500000;
type tree=^node;
     node=record
       left,right:tree;
       son:longint;
     end;
var range,xman,mini,a,b,n,m,i,j,k:longint;
    head,tail:array[1..maxn]of longint;
    gap,num:tree;
    st:string;
    ch:char;
procedure insert(now:tree;first,last,w:longint);
var mid:longint;
    t1:tree;
begin
  inc(now^.son);
  if first=last then exit;
  if now^.left=nil then
    begin
      new(t1);
      t1^.left:=nil;
      t1^.right:=nil;
      t1^.son:=0;
      now^.left:=t1;
      new(t1);
      t1^.left:=nil;
      t1^.right:=nil;
      t1^.son:=0;
      now^.right:=t1;
    end;
  mid:=(first+last) div 2;
  if w<=mid then insert(now^.left,first,mid,w)
            else insert(now^.right,mid+1,last,w);
end;
procedure delete(now:tree;first,last,w:longint);
var mid:longint;
begin
  dec(now^.son);
  if first=last then exit;
  mid:=(first+last) div 2;
  if w<=mid then delete(now^.left,first,mid,w)
            else delete(now^.right,mid+1,last,w);
end;
function findup(now:tree;first,last,a,b:longint):boolean;
var mid:longint;
begin
  if now^.son=0 then exit(false);
  if first=last then
    begin
      xman:=first;
      exit(true);
    end;
  mid:=(first+last) div 2;
  if a>mid then
    begin
      exit(findup(now^.right,mid+1,last,a,b));
    end else
  if b<=mid then
    begin
      exit(findup(now^.left,first,mid,a,b));
    end else
    begin
      if not findup(now^.right,mid+1,last,mid+1,b) then findup:=findup(now^.left,first,mid,a,mid)
        else exit(true);
    end;
end;
function findown(now:tree;first,last,a,b:longint):boolean;
var mid:longint;
begin
  if now^.son=0 then exit(false);
  if first=last then
    begin
      xman:=first;
      exit(true);
    end;
  mid:=(first+last) div 2;
  if a>mid then
    begin
      exit(findown(now^.right,mid+1,last,a,b));
    end else
  if b<=mid then
    begin
      exit(findown(now^.left,first,mid,a,b));
    end else
    begin
      if not findown(now^.left,first,mid,a,mid) then findown:=findown(now^.right,mid+1,last,mid+1,b)
        else findown:=true;
    end;
end;
begin
  assign(input,'form.in');
  reset(input);
  assign(output,'form.out');
  rewrite(output);
  readln(n,m);
  new(num);
  num^.left:=nil;
  num^.right:=nil;
  num^.son:=0;
  new(gap);
  gap^.left:=nil;
  gap^.right:=nil;
  gap^.son:=0;
  mini:=maxr;
  for i:=1 to n do
    begin
      read(head[i]);
      tail[i]:=head[i];
      if i<>1 then
        begin
        if mini>0 then
         begin
          range:=head[i]-mini+1;if range<0 then range:=0;
          if findup(num,0,maxr,range,head[i]) then mini:=abs(xman-head[i]);
          range:=head[i]+mini-1;if range>maxr then range:=maxr;
          if findown(num,0,maxr,head[i],range) then mini:=abs(xman-head[i]);
         end;
          insert(gap,0,maxr,abs(head[i]-tail[i-1]));
        end;
      insert(num,0,maxr,head[i]);
    end;
  readln;
  for i:=1 to m do
    begin
      st:='';
      read(ch);
      while ch in ['A'..'Z','_'] do
        begin
          st:=st+ch;
          read(ch);
        end;
      if st[1]='I' then
        begin
          read(a,b);
          if a<n then
            begin
              delete(gap,0,maxr,abs(head[a+1]-tail[a]));
              insert(gap,0,maxr,abs(head[a+1]-b));
            end;
          insert(gap,0,maxr,abs(b-tail[a]));
        if mini>0 then
         begin
          range:=b-mini+1;if range<0 then range:=0;
          if findup(num,0,maxr,range,b) then mini:=abs(xman-b);
          range:=b+mini-1;if range>maxr then range:=maxr;
          if findown(num,0,maxr,b,range) then mini:=abs(xman-b);
          insert(num,0,maxr,b);
         end;
          tail[a]:=b;
        end else
      if length(st)>7 then
        begin
          writeln(mini);
        end else
        begin
          findown(gap,0,maxr,0,maxr);
          writeln(xman);
        end;
      readln;
    end;
  close(input);
  close(output);
end.
