default:
	cd makeprocs; make
	cd n3_inj_proc; make
	cd h2o_inj_proc; make
	cd reaction_1_proc; make
	cd reaction_2_proc; make
	cd reaction_3_proc; make

clean:
	cd makeprocs; make clean
	cd n3_inj_proc; make clean
	cd h2o_inj_proc; make clean
	cd reaction_1_proc; make clean
	cd reaction_2_proc; make clean
	cd reaction_3_proc; make clean

run:
	cd ../../bin; dlxsim -x os.dlx.obj -a -u makeprocs.dlx.obj 3; ee469_fixterminal
