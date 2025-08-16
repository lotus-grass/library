{$r-,s-,q-}

const
  inf='book.in';
  ouf='book.out';
  maxn=100000;
  maxv=270000;
var
  v,sum :array[1..maxv] of longint;
  r :array[1..maxn] of longint;
  n,m,l,h,t,k,a :longint;
  d :integer;
  s :string;

procedure add(a,b,d :longint);
begin
  if d=1 then begin
    r[a]:=b; v[b]:=a;
  end else v[b]:=0;
  while b<=l do begin
    inc(sum[b],d);
    b:=b+b-(b and(b-1));
  end;
end;

function get(a :longint) :longint;
var s :longint;
begin
  s:=0;
  while a<>0 do begin
    s:=s+sum[a]; a:=a and(a-1);
  end;
  get:=s;
end;

function find(a :longint) :longint;
var h,t,q :longint;
begin
  h:=1; t:=l;
  while h<t do begin
    q:=(h+t)shr 1;
    if (q<=maxv)and(sum[q]<a) then begin
      a:=a-sum[q]; h:=q+1;
    end else t:=q;
  end;
  find:=h;
end;

begin
  assign(input,inf); reset(input);
  assign(output,ouf); rewrite(output);
  readln(n,m);
  k:=1;
  while 1 shl k<n+m+m do inc(k);
  l:=1 shl k;
  for k:=1 to n do begin
    read(a); add(a,k+m,1);
  end;
  readln;
  h:=m+1; t:=m+n;
  while m>0 do begin
    readln(s); dec(m);
    if s[1]='T' then begin
      delete(s,1,4); val(s,a,d);
      add(a,r[a],-1);
      dec(h); add(a,h,1);
    end else
    if s[1]='B' then begin
      delete(s,1,7); val(s,a,d);
      add(a,r[a],-1);
      inc(t); add(a,t,1);
    end else
    if s[1]='A' then begin
      delete(s,1,4); val(s,a,d);
      writeln(get(r[a])-1);
    end else
    if s[1]='Q' then begin
      delete(s,1,6); val(s,a,d);
      writeln(v[find(a)]);
    end else begin
      delete(s,1,7);
      k:=pos(' ',s);
      val(copy(s,1,k-1),a,d);
      if s[k+1]='0' then continue;
      if s[k+1]='1' then d:=1 else d:=-1;
      k:=find(get(r[a])+d);
      r[v[k]]:=r[a]; v[r[a]]:=v[k];
      r[a]:=k; v[k]:=a;
    end;
  end;
  close(input); close(output);
end.
