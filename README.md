# EDA-Algorithms<br>

This repository contains 3 EDA Algorithms written in C++ <br>

1) **Kernighan-Lin’s	bi-partitioning	algorithm**<br>	
*Objective*	is	to	minimize	the	number	of	edges	in	the	cut <br>
Input:	a	set	of	even	number	of	nodes	and	a	set	of	edges.	If	there	are	n	nodes,	the	node indices	are	continuous	integers	from	1	to	n.	 <br>
Format:	<br>
• The	first	line	has	two	numbers	–	the	number	of	nodes	followed	by	the	number	of	edges.	<br>
• Each	of	the	following	lines	has	two	numbers	that	are	indices	of	two	nodes	of	an	edge.	<br>
Output:		<br>
• Two	partitions,	each	of	which	is	described	by	the	indices	of	its	member	nodes.	<br>
• Cut	set,	represented	by	the	edges	in	the	cut,	an	edge	is	denoted	by	a	pair	of	node indices.	<br>
<br>

2) **Min cost A\* Search** <br>
*Objective:* To find the min-cost path between source and destination on a (manhattan)	grid	with	one	blockage	and	one	free-island<br>
![alt text](https://github.com/satishpasumarthi/EDA-Algorithms/blob/master/Grid.png  "Grid Example")
<br>
Input:	grid,	source	location,	target	location,	a	blockage	and	a	free	island.	<br>
Format:		<br>
Line	1	shows	number	of	rows,	followed	by	number	of	columns,	of	the	grid.	<br>
Line	2:	source	location	in	(row,	column)	indices.	<br>
Line	3:	target	location	in	(row,	column)	indices.	<br>
Line	4:	4	numbers	indicating	the	blockage.	<br>
Line	5:	4	numbers	indicating	the	free	island.	<br>
For	the	example	above,	the	input	file	is	like:	<br>
7				7	<br>
6				3	<br>
3				6	<br>
4				3				5			7	<br>
1				2				2			6	<br>
Output:		<br>
• Total	path	cost	of	the	solution.	<br>
• The	path	in	term	of	grid	cells	on	the	path.	<br>
For	the	example	above,	the	output	path	format	is	like:	<br>
(6,2)	(5,2)	(4,2)(3,2)(2,2)(2,3)(2,4)(2,5)(2,6)(3,6)	<br>
<br>

3) **Van Genniken Buffer Insertion** <br>
*Objective:* To	maximize	the	required	arrival	time	at	the	driver	node using	pi-model	for	each	wire	segment	(or	edge)	and	Elmore	delay	model.<br>	
Input:		<br>
• A	driver	node,	with	node	index	0	and	driver	resistance	of	1.	<br>
• n	sink	nodes,	indices	1,	2...n.	For	each	sink,	capacitance	and	required	arrival	time	are	given.	<br>
• n	–	1	Steiner	nodes,	with	indices	from	n+1	to	2n	–	1.	<br>
• A	set	of	directed	edges	represented	by	a	pair	of	nodes		(i,	j),	where	i	is	closer	to	the	driver	and	
j	is	closer	to	sinks	in	the	tree.	The	length	of	each	edge	is	also	provided.	<br>
• Wire	resistance	per	unit	length	is	1,	and	wire	capacitance	per	unit	length	is	also	1.	<br>
• The	routing	tree	is	a	binary	tree,	i.e.,	each	node	has	at	most	two	children	nodes.	<br>
• Each	upstream	node	of	an	edge	is	a	candidate	buffer	location.		<br>
• One	buffer	type,	with	resistance	1,	capacitance	1	and	intrinsic	delay	1.<br>		
Input	File	Format:		<br>
• The	first	line	has	one	number	–	the	number	of	sinks	n.	<br>
• Line	 2	 to	 line	 n	 +	 1	 are	 information	 for	 sink	 1	 to	 n,	 with	 each	 line	 has	 two	 numbers:	 sink	
capacitance	and	required	arrival	time.	<br>
• Next	2n	–	1	lines	are	edge	information.	Each	line	corresponds	to	one	edge,	and	has	3	numbers:	<br>
upstream	node	index,	downstream	node	index,	and	edge	length.									<br>
Output:		<br>
• Total	number	of	buffers	inserted.	<br>
• The	nodes	where	buffers	are	inserted.	<br>
• The	required	arrival	time	at	the	driver	node.	<br>
