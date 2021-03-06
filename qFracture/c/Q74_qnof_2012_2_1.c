/* 
 * Copyright 2012 ClinRisk Ltd.
 * 
 * This file is part of QFracture-2012 (http://qfracture.org, http://svn.clinrisk.co.uk/qfracture).
 * 
 * QFracture-2012 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * QFracture-2012 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with QFracture-2012.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Additional terms
 * 
 * The following disclaimer must be displayed alongside any risk score generated by this code.
 *   The initial version of this file, to be found at http://svn.clinrisk.co.uk/qfracture, faithfully implements QFracture-2012.
 *   We have released this code under the GNU Lesser General Public License to enable others to implement the algorithm faithfully.
 *   However, the nature of the GNU Lesser General Public License is such that we cannot prevent, for example, someone altering the coefficients.
 *   We stress, therefore, that it is the responsibility of the end user to check that the source that they receive produces the same results as the original code posted at http://svn.clinrisk.co.uk/qfracture.
 *   Inaccurate implementations of risk scores can lead to wrong patients being given the wrong treatment.
 * 
 * This file has been auto-generated.
 * XML source: Q74_qnof_2012_2_1.xml
 * STATA dta time stamp: 1 Mar 2012 11:21
 * This file was created on: Mon  5 Mar 2012 11:14:42 GMT
 */

#include <math.h>
#include <string.h>
#include <clinrisk/Q74_qnof_2012_2_1.h>
#include <clinrisk/utils.h>

static double nof_male_raw(
int age,int alcohol_cat6,int b_antidepressant,int b_anycancer,int b_asthmacopd,int b_carehome,int b_corticosteroids,int b_cvd,int b_dementia,int b_epilepsy2,int b_falls,int b_fracture4,int b_liver,int b_parkinsons,int b_ra_sle,int b_renal,int b_type1,int b_type2,double bmi,int ethrisk,int fh_osteoporosis,int smoke_cat,int surv
)
{
	double survivor[19] = {
		0,
		0.999958395957947,
		0.999915361404419,
		0.999862074851990,
		0.999795675277710,
		0.999720335006714,
		0.999637126922607,
		0.999530315399170,
		0.999413371086121,
		0.999267756938934,
		0.999112963676453,
		0.998929023742676,
		0.998713493347168,
		0.998442947864532,
		0.998135447502136,
		0.997829139232636,
		0.997516810894012,
		0.997076392173767,
		0.996633410453796
	};

	/* The conditional arrays */

	double Ialcohol[6] = {
		0,
		-0.1883071508763912700000000,
		-0.1456237141772618900000000,
		-0.1131015985038896200000000,
		0.2669108383852995000000000,
		0.7159049108970482200000000
	};
	double Iethrisk[10] = {
		0,
		0,
		-0.4720554035932271700000000,
		-0.4404885564307023900000000,
		-2.0311044284508650000000000,
		-0.8877544935355209400000000,
		-1.5093354044488063000000000,
		-0.1169655869663822200000000,
		-0.7810018330580403800000000,
		-0.2253671795533221900000000
	};
	double Ismoke[5] = {
		0,
		-0.0156465395681702860000000,
		0.2947168223225690200000000,
		0.4319073634973120700000000,
		0.4937619134916043700000000
	};

	/* Applying the fractional polynomial transforms */
	/* (which includes scaling)                      */

	double dage = age;
	dage=dage/10;
	double age_1 = pow(dage,3);
	double age_2 = pow(dage,3)*log(dage);
	double dbmi = bmi;
	dbmi=dbmi/10;
	double bmi_1 = pow(dbmi,-2);

	/* Centring the continuous variables */

	age_1 = age_1 - 117.376983642578130;
	age_2 = age_2 - 186.449066162109370;
	bmi_1 = bmi_1 - 0.142089113593102;

	/* Start of Sum */
	double a=0;

	/* The conditional sums */

	a += Ialcohol[alcohol_cat6];
	a += Iethrisk[ethrisk];
	a += Ismoke[smoke_cat];

	/* Sum from continuous values */

	a += age_1 * 0.0470956645877030970000000;
	a += age_2 * -0.0173232541198013180000000;
	a += bmi_1 * 6.9051198985719147000000000;

	/* Sum from boolean values */

	a += b_antidepressant * 0.5222696860482879400000000;
	a += b_anycancer * 0.3904642661797034200000000;
	a += b_asthmacopd * 0.2955316362120945000000000;
	a += b_carehome * 0.7180133962015686800000000;
	a += b_corticosteroids * 0.1637845766085505300000000;
	a += b_cvd * 0.2685578286436679000000000;
	a += b_dementia * 0.9660867715544014800000000;
	a += b_epilepsy2 * 0.8977271850145135400000000;
	a += b_falls * 0.5314298176292541200000000;
	a += b_fracture4 * 0.7025297516317516900000000;
	a += b_liver * 0.7566576273364045100000000;
	a += b_parkinsons * 1.0980688140356138000000000;
	a += b_ra_sle * 0.6434807364258057200000000;
	a += b_renal * 0.5918218708907634400000000;
	a += b_type1 * 1.5742324490573854000000000;
	a += b_type2 * 0.2887768858842130200000000;
	a += fh_osteoporosis * 1.2332490177632631000000000;

	/* Sum from interaction terms */


	/* Calculate the score itself */
	double score = 100.0 * (1 - pow(survivor[surv], exp(a)) );
	return score;
}

static int nof_male_validation(
int age,int alcohol_cat6,int b_antidepressant,int b_anycancer,int b_asthmacopd,int b_carehome,int b_corticosteroids,int b_cvd,int b_dementia,int b_epilepsy2,int b_falls,int b_fracture4,int b_liver,int b_parkinsons,int b_ra_sle,int b_renal,int b_type1,int b_type2,double bmi,int ethrisk,int fh_osteoporosis,int smoke_cat,int surv,char *errorBuf,int errorBufSize
)
{
	int ok=1;
	*errorBuf=0;
	if (!i_in_range(age,30,100)) {
		ok=0;
		strlcat(errorBuf,"error: age must be in range (30,100)\n",errorBufSize);
	}
	if (!i_in_range(alcohol_cat6,0,5)) {
		ok=0;
		strlcat(errorBuf,"error: alcohol_cat6 must be in range (0,5)\n",errorBufSize);
	}
	if (!is_boolean(b_antidepressant)) {
		ok=0;
		strlcat(errorBuf,"error: b_antidepressant must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_anycancer)) {
		ok=0;
		strlcat(errorBuf,"error: b_anycancer must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_asthmacopd)) {
		ok=0;
		strlcat(errorBuf,"error: b_asthmacopd must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_carehome)) {
		ok=0;
		strlcat(errorBuf,"error: b_carehome must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_corticosteroids)) {
		ok=0;
		strlcat(errorBuf,"error: b_corticosteroids must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_cvd)) {
		ok=0;
		strlcat(errorBuf,"error: b_cvd must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_dementia)) {
		ok=0;
		strlcat(errorBuf,"error: b_dementia must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_epilepsy2)) {
		ok=0;
		strlcat(errorBuf,"error: b_epilepsy2 must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_falls)) {
		ok=0;
		strlcat(errorBuf,"error: b_falls must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_fracture4)) {
		ok=0;
		strlcat(errorBuf,"error: b_fracture4 must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_liver)) {
		ok=0;
		strlcat(errorBuf,"error: b_liver must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_parkinsons)) {
		ok=0;
		strlcat(errorBuf,"error: b_parkinsons must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_ra_sle)) {
		ok=0;
		strlcat(errorBuf,"error: b_ra_sle must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_renal)) {
		ok=0;
		strlcat(errorBuf,"error: b_renal must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_type1)) {
		ok=0;
		strlcat(errorBuf,"error: b_type1 must be in range (0,1)\n",errorBufSize);
	}
	if (!is_boolean(b_type2)) {
		ok=0;
		strlcat(errorBuf,"error: b_type2 must be in range (0,1)\n",errorBufSize);
	}
	if (!d_in_range(bmi,20,40)) {
		ok=0;
		strlcat(errorBuf,"error: bmi must be in range (20,40)\n",errorBufSize);
	}
	if (!i_in_range(ethrisk,1,9)) {
		ok=0;
		strlcat(errorBuf,"error: ethrisk must be in range (1,9)\n",errorBufSize);
	}
	if (!is_boolean(fh_osteoporosis)) {
		ok=0;
		strlcat(errorBuf,"error: fh_osteoporosis must be in range (0,1)\n",errorBufSize);
	}
	if (!i_in_range(smoke_cat,0,4)) {
		ok=0;
		strlcat(errorBuf,"error: smoke_cat must be in range (0,4)\n",errorBufSize);
	}
	if (!i_in_range(surv,1,18)) {
		ok=0;
		strlcat(errorBuf,"error: surv must be in range (1,18)\n",errorBufSize);
	}
	return ok;
}

double nof_male(
int age,int alcohol_cat6,int b_antidepressant,int b_anycancer,int b_asthmacopd,int b_carehome,int b_corticosteroids,int b_cvd,int b_dementia,int b_epilepsy2,int b_falls,int b_fracture4,int b_liver,int b_parkinsons,int b_ra_sle,int b_renal,int b_type1,int b_type2,double bmi,int ethrisk,int fh_osteoporosis,int smoke_cat,int surv,int *error,char *errorBuf,int errorBufSize
)
{
	*error = 0;	int ok = nof_male_validation(age,alcohol_cat6,b_antidepressant,b_anycancer,b_asthmacopd,b_carehome,b_corticosteroids,b_cvd,b_dementia,b_epilepsy2,b_falls,b_fracture4,b_liver,b_parkinsons,b_ra_sle,b_renal,b_type1,b_type2,bmi,ethrisk,fh_osteoporosis,smoke_cat,surv,errorBuf,errorBufSize);
	if(!ok) { 
		*error = 1;
		return 0.0;
	}
	return nof_male_raw(age,alcohol_cat6,b_antidepressant,b_anycancer,b_asthmacopd,b_carehome,b_corticosteroids,b_cvd,b_dementia,b_epilepsy2,b_falls,b_fracture4,b_liver,b_parkinsons,b_ra_sle,b_renal,b_type1,b_type2,bmi,ethrisk,fh_osteoporosis,smoke_cat,surv);
}
