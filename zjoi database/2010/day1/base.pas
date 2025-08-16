(*
 *Program:ZJOI2010_Day1_Problem3_base
 *Author:Celery.T
 *Date:June 16th,2010
 *Kind:Dynamic Programming & Segment Tree
 *State:Solved
*)

uses math;

const
	mn=40000;
	size=mn << 1;
	oo=2000000000;
type
	segnode=record
				key,mark:longint;
			end;
var
	tree:array[1..size]of segnode;
	f,d,c,s,w,b,e,p,before:array[0..mn]of longint;
	n,m,ans:longint;

procedure swap(var a,b:longint);
	var t:longint;
	begin
		t:=a;a:=b;b:=t;
	end;

procedure qsort(h,t:longint);
	var i,j,k:longint;
	begin
		i:=h;j:=t;k:=e[(h+t) >> 1];
		while i<=j do
			begin
				while e[i]<k do inc(i);
				while e[j]>k do dec(j);
				if i<=j then
					begin
						swap(e[i],e[j]);
						swap(p[i],p[j]);
						inc(i);
						dec(j);
					end;
			end;
		if i<t then qsort(i,t);
		if h<j then qsort(h,j);
	end;

procedure init;
	var i,l,r,mid:longint;
	begin
		assign(input,'base.in');
		reset(input);
		readln(n,m);
		d[0]:=-oo;d[1]:=0;d[n+1]:=oo;
		for i:=2 to n do read(d[i]);
		for i:=1 to n do read(c[i]);
		for i:=1 to n do read(s[i]);
		for i:=1 to n do read(w[i]);
		for i:=1 to n do
			begin
				b[i]:=d[i]-s[i];
				e[i]:=d[i]+s[i];
				p[i]:=i;
				l:=0;r:=i-1;
				while l<=r do
					begin
						mid:=(l+r) >> 1;
						if d[mid]<b[i] then
							begin
								before[i]:=mid;
								l:=mid+1;
							end
						else r:=mid-1;
					end;
			end;
		qsort(1,n);
	end;

procedure build(t,l,r,p:longint);
	var mid:longint;
	begin
		tree[t].mark:=0;
		if l=r then
			tree[t].key:=f[p]
		else begin
			mid:=(l+r) >> 1;
			if p<=mid then
				build(t << 1,l,mid,p)
			else build(t << 1+1,mid+1,r,p);
			tree[t].key:=min(tree[t << 1].key,tree[t << 1+1].key);
		end;
	end;

procedure pushdown(t:longint);
	begin
		if t << 1>size then
			exit;
		if tree[t].mark=0 then
			exit;
		inc(tree[t << 1].key,tree[t].mark);
		inc(tree[t << 1].mark,tree[t].mark);
		inc(tree[t << 1+1].key,tree[t].mark);
		inc(tree[t << 1+1].mark,tree[t].mark);
		tree[t].mark:=0;
	end;

procedure modify(t,l,r,x,y,w:longint);
	var mid:longint;
	begin
		if(l=x)and(r=y)then
			begin
				inc(tree[t].key,w);
				inc(tree[t].mark,w);
			end
		else begin
			pushdown(t);
			mid:=(l+r) >> 1;
			if y<=mid then
				modify(t << 1,l,mid,x,y,w)
			else if x>mid then
				modify(t << 1+1,mid+1,r,x,y,w)
			else begin
				modify(t << 1,l,mid,x,mid,w);
				modify(t << 1+1,mid+1,r,mid+1,y,w);
			end;
			tree[t].key:=min(tree[t << 1].key,tree[t << 1+1].key);
		end;
	end;

procedure main;
	var i,j,k:longint;
	begin
		filldword(f,sizeof(f) >> 2,oo);
		f[0]:=0;
		for i:=0 to n do
			build(1,0,n,i);
		ans:=oo;
		for k:=1 to m+1 do
			begin
				for i:=0 to k-1 do f[i]:=oo;
				j:=1;
				for i:=k to n+1 do
					begin
						while(j<=n)and(d[i]>e[j])do
							begin
                                if before[p[j]]>=k-1 then
									modify(1,0,n,k-1,before[p[j]],w[p[j]]);
								inc(j);
							end;
						f[i]:=tree[1].key+c[i];
					end;
				if ans>f[n+1] then ans:=f[n+1];
				for i:=0 to n do build(1,0,n,i);
			end;
	end;

procedure print;
	begin
		assign(output,'base.out');
		rewrite(output);
		writeln(ans);
		close(output);
	end;

begin
	init;
	main;
	print;
end.