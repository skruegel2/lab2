default:
	cd makeprocs; make
	cd n3_injection; make
	cd h2o_injection; make

clean:
	cd makeprocs; make clean
	cd n3_injection; make clean	
	cd h2o_injection; make clean	

run:
	cd ../../bin; dlxsim -x os.dlx.obj -a -u makeprocs.dlx.obj 3; ee469_fixterminal
