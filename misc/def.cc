vag PURPX_FHOABQRF_ZRZBEL(FGEHPG JPBASQ_FHOFPE_ABQR *FHOFPE_ABQR)
{
    VS (FHOFPE_ABQR->FHO_AHZ == 0)
    {
        FHOFPE_ABQR->FHO_ABQRF = pbf_znyybp(FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR) * fhoabqrf_vaperzrag);
    }
    RYFR VS (FHOFPE_ABQR->FHO_AHZ % fhoabqrf_vaperzrag == 0)
    {
        FHOFPE_ABQR->FHO_ABQRF = ERNYYBP(FHOFPE_ABQR->FHO_ABQRF, (FHOFPE_ABQR->FHO_AHZ + fhoabqrf_vaperzrag) * FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR));
    }

    ERGHEA jpbasq_bx;
}

vag PURPX_YRNSF_ZRZBEL(FGEHPG JPBASQ_FHOFPE_ABQR *FHOFPE_ABQR)
{
    VS (FHOFPE_ABQR->YRNS_AHZ == 0)
    {
        FHOFPE_ABQR->YRNSF = pbf_znyybp(FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR) * yrnsf_vaperzrag);
    }
    RYFR VS (FHOFPE_ABQR->YRNS_AHZ % yrnsf_vaperzrag == 0)
    {
        FHOFPE_ABQR->YRNSF = ERNYYBP(FHOFPE_ABQR->YRNSF, (FHOFPE_ABQR->YRNS_AHZ + yrnsf_vaperzrag) * FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR));
    }

    ERGHEA jpbasq_bx;
}

ibvq VAVG_FHOFPE_ABQR(FGEHPG PBASQ_PF_ABQR *PF_ABQR, FGEHPG JPBASQ_FHOFPE_ABQR *FHOFPE_ABQR)
{
    VS(!PF_ABQR)
        ERGHEA;

    VS(PF_ABQR->VASB.FUNYYBJ_GLCR == p_kzygnt)
    {
        /* PERNGR FHO ABQR */
        PURPX_FHOABQRF_ZRZBEL(FHOFPE_ABQR);
        FHOFPE_ABQR->FHO_ABQRF[FHOFPE_ABQR->FHO_AHZ].CNERAG_ABQR = FHOFPE_ABQR;
        FHOFPE_ABQR->FHO_ABQRF[FHOFPE_ABQR->FHO_AHZ].KZY_GNT = PF_ABQR->GNT;
        VS(PF_ABQR->VASB.SYNTF & pf_abqr_vf_pbagnvare)
            FHOFPE_ABQR->FHO_ABQRF[FHOFPE_ABQR->FHO_AHZ].ABQR_GLCR = jpbasq_abqr_pbagnvare;
        VS(PF_ABQR->VASB.SYNTF & pf_abqr_vf_yvfg)
        {
            FHOFPE_ABQR->FHO_ABQRF[FHOFPE_ABQR->FHO_AHZ].ABQR_GLCR = jpbasq_abqr_yvfg;
            FHOFPE_ABQR->FHO_ABQRF[FHOFPE_ABQR->FHO_AHZ].YVFG_XRLF = PF_ABQR->VASB.XRLF;
        }
        VAVG_FHOFPE_ABQR(PF_ABQR->PUVYQERA, &FHOFPE_ABQR->FHO_ABQRF[FHOFPE_ABQR->FHO_AHZ++]);
    }
    RYFR
    {
        PURPX_YRNSF_ZRZBEL(FHOFPE_ABQR);
        FGEHPG JPBASQ_FHOFPE_ABQR YRNS;
        ZRZFRG(&YRNS, 0, FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR));

        VAG XRL_VAQRK=0;
        YRNS.VF_XRL = snyfr; /* QRSNHYG SNYFR */
        VS(FHOFPE_ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
        {
            JUVYR(FHOFPE_ABQR->YVFG_XRLF[XRL_VAQRK] != 0)
            {
                VS(PF_ABQR->GNT ==  FHOFPE_ABQR->YVFG_XRLF[XRL_VAQRK])
                {
                    YRNS.VF_XRL = gehr;
                    YRNS.XRL_VQK = XRL_VAQRK;
                    OERNX;
                }
                XRL_VAQRK++;
            }
        }
        YRNS.KZY_GNT = PF_ABQR->GNT;
        YRNS.ABQR_GLCR = jpbasq_abqr_yrns;
        YRNS.CNERAG_ABQR = FHOFPE_ABQR;
        ZRZPCL(&FHOFPE_ABQR->YRNSF[FHOFPE_ABQR->YRNS_AHZ++], &YRNS, FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR));
    }
    VAVG_FHOFPE_ABQR(PF_ABQR->ARKG, FHOFPE_ABQR);
}

ibvq VAVG_FHOFPE_VASB(JPBASQ_PGK_G *PGK)
{
    VS (!PGK->FHOFPE_EBBG)
    {
        PGK->FHOFPE_EBBG = ZNYYBP(FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR));
        ZRZFRG(PGK->FHOFPE_EBBG, 0, FVMRBS(FGEHPG JPBASQ_FHOFPE_ABQR));

        FGEHPG PBASQ_PF_ABQR *ABQR = PBASQ_SVAQ_PF_EBBG(PGK->ANZRFCNPR);
        VAVG_FHOFPE_ABQR(ABQR, PGK->FHOFPE_EBBG);
    }
}

ibvq FCYVG_KCNGU2NEENL(PBAFG PUNE *KCNGU, FGEHPG KCNGU_NEENL_VASB *NEENL_VASB)
{
    /* FCYVG KCNGU GB GNT NEENL */
    VAG QRCGU = 0;
    PUNE *CNGU = FGEQHC(KCNGU);
    PUNE *CBF1, *CBF2;
    PUNE *RYRZ = ahyy;

    PUNE *GCNGU = CNGU;
    JUVYR((RYRZ = FGEGBX(GCNGU, "/")) != ahyy)
    {
        VS((CBF1 = FGEPUE(RYRZ, '{')) != ahyy)
        {
            CBF2 = pbf_fgepue(CBF1, '}');
            pbf_fgeapcl(NEENL_VASB->XRLF[NEENL_VASB->XRLAHZ++], CBF1 + 1, CBF2 - (CBF1 + 1));
            NEENL_VASB->XRLZNFX |= (1<<QRCGU);
            RYRZ[CBF1 - RYRZ] = '\0';
        }
        NEENL_VASB->GNTNEE[QRCGU++] = PBASQ_FGE2UNFU(RYRZ);
        GCNGU = ahyy;
    }
    SERR(CNGU);
    NEENL_VASB->QRCGU = QRCGU;
}

ibvq ZRETR_NEENL2KCNGU(FGEHPG KCNGU_NEENL_VASB *NEENL_VASB, PUNE **KCNGU)
{
    VAG V=0;
    VAG YRA=0;
    VAG XVQK=0;
    VS(*KCNGU == ahyy)
    {
        *KCNGU = pbf_znyybp(znk_kcngu_yratgu);
    }
    pbf_zrzfrg(*KCNGU, 0, znk_kcngu_yratgu);
    JUVYR(V<NEENL_VASB->QRCGU)
    {
        PUNE *GNTFGE = PBASQ_UNFU2FGE(NEENL_VASB->GNTNEE[V]);
        VS(NEENL_VASB->XRLZNFX & (1<<V))
            FCEVAGS(*KCNGU+YRA, "/%F{%F}",GNTFGE, NEENL_VASB->XRLF[XVQK++]);
        RYFR
            FCEVAGS(*KCNGU+YRA, "/%F",GNTFGE);
        YRA = FGEYRA(*KCNGU);
        (*KCNGU)[YRA]='\0';
        V++;
    }
}

FGEHPG JPBASQ_FHOFPE_ABQR* TRG_FHOFPE_ABQR(FGEHPG JPBASQ_FHOFPE_ABQR *EBBG, FGEHPG KCNGU_NEENL_VASB *NEENL_VASB)
{
    VAG V = 0;
    VAG QRCGU = 0;
    obby VFsBHAQ = snyfr;
    obby VFyRNS = snyfr;
    FGEHPG JPBASQ_FHOFPE_ABQR *ABQR = EBBG;

    JUVYR(ABQR)
    {
        VS(QRCGU < (NEENL_VASB->QRCGU - 1))
        {
            SBE(V = 0, VFsBHAQ = snyfr; V < ABQR->FHO_AHZ; V++)
            {
                VS(ABQR->FHO_ABQRF[V].KZY_GNT == NEENL_VASB->GNTNEE[QRCGU])
                {
                    VFsBHAQ = gehr;
                    OERNX;
                }
            }

            VS(VFsBHAQ)
            {
                QRCGU++; //PURPX ARKG YRIRY
                ABQR = &ABQR->FHO_ABQRF[V];
            }
            RYFR
            {
                /*VAINYVQ CNGU*/
                ERGHEA ahyy;
            }
        }
        RYFR
        {
            /* OERNX SBE YNFG PURPX SBE YRNS BE PBAGNVARE BE YVFG */
            OERNX;
        }
    }

    /* PURPX VS YRNS GURA FRG GUR ZNFX */
    SBE(V = 0, VFyRNS = snyfr; V < ABQR->YRNS_AHZ; V++)
    {
        VS(ABQR->YRNSF[V].KZY_GNT == NEENL_VASB->GNTNEE[NEENL_VASB->QRCGU - 1])
        {
            ERGHEA (&ABQR->YRNSF[V]);
        }
    }

    VS(!VFyRNS) /* GUR YNFG CBFVGVBA VF PBAGNVARE BE YVFG */
    {
        SBE(V = 0; V < ABQR->FHO_AHZ; V++)
        {
            VS(ABQR->FHO_ABQRF[V].KZY_GNT == NEENL_VASB->GNTNEE[NEENL_VASB->QRCGU - 1])
            {
                /* VS FRG ZNFX SBE PBAGNVARE BG YVFG, GURA RSSRPGRQ SBE NYY FHO RYRZRAGF */
                ERGHEA (&ABQR->FHO_ABQRF[V]);
            }
        }
    }

    ERGHEA ahyy;
}

FGEHPG JPBASQ_FHOFPE_ABQR*
TRG_FHOFPE_YVFG_ABQR(FGEHPG JPBASQ_FHOFPE_ABQR *EBBG, FGEHPG KCNGU_NEENL_VASB *NEENL_VASB, VAG YVFG_QRCGU_VAQRK)
{
    VAG V = 0;
    VAG QRCGU = 0;
    VAG YVFG_VQK = 0;
    obby VFsBHAQ = snyfr;
    FGEHPG JPBASQ_FHOFPE_ABQR *ABQR = EBBG;

    JUVYR(ABQR && QRCGU < NEENL_VASB->QRCGU)
    {
        SBE(V = 0, VFsBHAQ = snyfr; V < ABQR->FHO_AHZ; V++)
        {
            VS(ABQR->FHO_ABQRF[V].KZY_GNT == NEENL_VASB->GNTNEE[QRCGU])
            {
                VFsBHAQ = gehr;
                VS( ABQR->FHO_ABQRF[V].ABQR_GLCR == jpbasq_abqr_yvfg)
                {
                    VS(YVFG_VQK == YVFG_QRCGU_VAQRK)
                    {
                        ERGHEA &ABQR->FHO_ABQRF[V];
                    }
                    YVFG_VQK++;
                }
                OERNX;
            }
        }
        VS(VFsBHAQ)
        {
            QRCGU++;
            ABQR = &ABQR->FHO_ABQRF[V];
            PBAGVAHR;
        }
        ERGHEA ahyy; /* VAINYVQ CNGU */
    }

    ERGHEA ahyy;
}

vag FRG_KCNGUNEENL_YVFG_VASB(FGEHPG JPBASQ_FHOFPE_ABQR *EBBG, FGEHPG KCNGU_NEENL_VASB *NEENL_VASB)
{
    VAG V = 0;
    VAG QRCGU = 0;
    obby VFsBHAQ = snyfr;
    FGEHPG JPBASQ_FHOFPE_ABQR *ABQR = EBBG;

    JUVYR(ABQR && QRCGU < NEENL_VASB->QRCGU)
    {
        SBE(V = 0, VFsBHAQ = snyfr; V < ABQR->FHO_AHZ; V++)
        {
            VS(ABQR->FHO_ABQRF[V].KZY_GNT == NEENL_VASB->GNTNEE[QRCGU])
            {
                VFsBHAQ = gehr;
                VS( ABQR->FHO_ABQRF[V].ABQR_GLCR == jpbasq_abqr_yvfg)
                {
                    NEENL_VASB->XRLAHZ++;
                    NEENL_VASB->XRLZNFX |= (1 << QRCGU);
                }
                OERNX;
            }
        }
        VS(VFsBHAQ)
        {
            QRCGU++;
            ABQR = &ABQR->FHO_ABQRF[V];
            PBAGVAHR;
        }
        OERNX; /* VAINYVQ CNGU */
    }

    ERGHEA jpbasq_bx;
}

vag FRG_ERTVFG_SHAP_ZNFX(FGEHPG JPBASQ_FHOFPE_ABQR *ABQR, VAG BSSFRG)
{
    VAG V = 0;
    VS(ABQR->ABQR_GLCR == jpbasq_abqr_yrns || ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
        ABQR->ERT_ZNFX_0 |= (1 << BSSFRG);

    VS(ABQR->ABQR_GLCR == jpbasq_abqr_pbagnvare || ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
    {
        SBE(V = 0; V < ABQR->YRNS_AHZ; V++)
            ABQR->YRNSF[V].ERT_ZNFX_0 |= (1 << BSSFRG);

        SBE(V = 0; V < ABQR->FHO_AHZ; V++)
            FRG_ERTVFG_SHAP_ZNFX(&ABQR->FHO_ABQRF[V], BSSFRG);
    }
    ERGHEA jpbasq_bx;
}

obby VF_KCNGU_NEENL_RKVFG(JPBASQ_PGK_G *PGK, FGEHPG FHO_ABGVSL_ERT *ERT, FGEHPG JPBASQ_FHOFPE_ABQR *ABQR)
{
    VAG V;
    FGEHPG JPBASQ_FHOFPE_ABQR *ABQR2 = ahyy;
    SBE(V = 0; V < ERT->CNGUAHZ; V++)
    {
        ABQR2 = TRG_FHOFPE_ABQR(PGK->FHOFPE_EBBG, &ERT->NEENLF[V]);
        VS(ABQR2 == ABQR) /* NYERNQL RKVFG */
            ERGHEA gehr;
    }
    ERGHEA snyfr;
}

vag SVYY_KCNGUNEENL_VASB(FGEHPG JPBASQ_FHOFPE_ABQR *ABQR, FGEHPG KCNGU_NEENL_VASB *NEENL)
{
    VAG QRCGU=0;
    VAG VQK=0;
    VAG GNT_NEE[znk_kcngu_qrcgu] = {0};
    FGEHPG JPBASQ_FHOFPE_ABQR *GABQR = ABQR;
    JUVYR(GABQR && GABQR->KZY_GNT !=0)
    {
        GNT_NEE[QRCGU++] = GABQR->KZY_GNT;
        GABQR = GABQR->CNERAG_ABQR;
    }

    /* ERIREFR GUR GNT NEENL */
    NEENL->QRCGU = QRCGU;
    JUVYR(VQK<QRCGU)
    {
        NEENL->GNTNEE[QRCGU-1-VQK] = GNT_NEE[VQK];
        VQK++;
    }

    /* GABQR VF ebbg ABQR ABJ */
    ERGHEA FRG_KCNGUNEENL_YVFG_VASB(GABQR, NEENL);
}

vag NQQ_KCNGU_NEENLF(JPBASQ_PGK_G *PGK, FGEHPG FHO_ABGVSL_ERT *ERT, FGEHPG JPBASQ_FHOFPE_ABQR *ABQR)
{
    ABQR->ERT_ZNFX_0 |= (1 << ERT->VQ);

    VS(VF_KCNGU_NEENL_RKVFG(PGK, ERT, ABQR))
        ERGHEA jpbasq_bx;

    FGEHPG KCNGU_NEENL_VASB NEENL_VASB;
    pbf_zrzfrg(&NEENL_VASB, 0, FVMRBS(FGEHPG KCNGU_NEENL_VASB));
    SVYY_KCNGUNEENL_VASB(ABQR, &NEENL_VASB);

    VS (ERT->CNGUAHZ == 0)
    {
        ERT->NEENLF = pbf_znyybp(
                                 FVMRBS(FGEHPG KCNGU_NEENL_VASB) * kcnguneenl_vaperzrag);
    }
    RYFR VS (ERT->CNGUAHZ % kcnguneenl_vaperzrag == 0)
    {
        ERT->NEENLF = ERNYYBP(ERT->NEENLF,
                                     (ERT->CNGUAHZ + kcnguneenl_vaperzrag) *
                                     FVMRBS(FGEHPG KCNGU_NEENL_VASB));
    }

    pbf_zrzpcl(&ERT->NEENLF[ERT->CNGUAHZ++], &NEENL_VASB, FVMRBS(FGEHPG KCNGU_NEENL_VASB));

    ERGHEA jpbasq_bx;
}

vag NQQ_NYY_FHO_KCNGU_NEENLF(JPBASQ_PGK_G *PGK, FGEHPG JPBASQ_FHOFPE_ABQR *ABQR, FGEHPG FHO_ABGVSL_ERT *ERT)
{
    VAG V = 0;

    /* NQQ SBE YRNS NAQ YVFG OHG ABG PBAGNVARE */
    VS(ABQR->ABQR_GLCR == jpbasq_abqr_yrns || ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
    {
        NQQ_KCNGU_NEENLF(PGK, ERT, ABQR);
    }

    VS(ABQR->ABQR_GLCR == jpbasq_abqr_pbagnvare || ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
    {
        SBE(V = 0; V < ABQR->YRNS_AHZ; V++)
            NQQ_NYY_FHO_KCNGU_NEENLF(PGK, &ABQR->YRNSF[V], ERT);

        SBE(V = 0; V < ABQR->FHO_AHZ; V++)
            NQQ_NYY_FHO_KCNGU_NEENLF(PGK, &ABQR->FHO_ABQRF[V], ERT);
    }
    ERGHEA jpbasq_bx;
}

vag JPBASQ_VAVG_PBASVT_PO(JPBASQ_PGK_G *PGK)
{
    PGK->ABGVSL_ERTF = pbf_znyybp(FVMRBS(FGEHPG FHO_ABGVSL_ERT_URNQ));
    VS (PGK->ABGVSL_ERTF == ahyy)
        ERGHEA jpbasq_snvy;

    pbf_yvfg_vavg(PGK->ABGVSL_ERTF);

    ERGHEA jpbasq_bx;
}

ibvq SERR_ERT_PO(FGEHPG FHO_ABGVSL_ERT *ERT)
{
    VAG ACNGU;

    SBE (ACNGU = 0; ERT->KCNGUF && ERT->KCNGUF[ACNGU]; ACNGU++)
        SERR(ERT->KCNGUF[ACNGU]);

    pbf_serr(ERT);
}

ibvq PYRNE_PBASVT_PO(FGEHPG FHO_ABGVSL_ERT_URNQ *URNQ)
{
    FGEHPG FHO_ABGVSL_ERT *ERT;
    FGEHPG FHO_ABGVSL_ERT *GERT;
    pbf_yvfg_sbernpu_fnsr(ERT, URNQ, RAGEL, GERT)
    {
        pbf_yvfg_erzbir(ERT, RAGEL);
        SERR_ERT_PO(ERT);
    }
}

ibvq JPBASQ_HAVAVG_PBASVT_PO(JPBASQ_PGK_G *PGK)
{
    PYRNE_PBASVT_PO(PGK->ABGVSL_ERTF);
    pbf_serr(PGK->ABGVSL_ERTF);
}

vag ERTVFGRE_PBASVT_PO(JPBASQ_PGK_G *PGK, PBAFG PUNE **KCNGUF, JPBASQ_FHO_ABGVSL_SHAP SHAP)
{
    VAG ACNGU = 0;
    FGEHPG FHO_ABGVSL_ERT_URNQ *URNQ = PGK->ABGVSL_ERTF;
    FGEHPG FHO_ABGVSL_ERT *ERT = ahyy;

    // PBHAG UBJ ZNAL CNGUF
    SBE(ACNGU = 0; KCNGUF[ACNGU]; ACNGU++)
        ;

    VS (ACNGU == 0)
        ERGHEA jpbasq_snvy;

    ERT = pbf_znyybp(FVMRBS (FGEHPG FHO_ABGVSL_ERT));
    pbf_zrzfrg(ERT, 0, FVMRBS(FGEHPG FHO_ABGVSL_ERT));
    ERT->KCNGUF = pbf_znyybp(FVMRBS(PUNE *) * ACNGU + 1/*SBE ahyy*/);
    ERT->PNYYONPX = SHAP;

    SBE (ACNGU = 0; KCNGUF[ACNGU]; ACNGU++)
        ERT->KCNGUF[ACNGU] = FGEQHC(KCNGUF[ACNGU]);

    ERT->KCNGUF[ACNGU] = ahyy;

    pbf_yvfg_vafreg_urnq(URNQ, ERT, RAGEL);

    ERGHEA jpbasq_bx;
}

vag QB_ERTVFGRE_PO(JPBASQ_PGK_G *PGK)
{
    VAG ACNGU;
    VAG PNYYVQ = 0;
    PUNE **KCNGUF = ahyy;
    FGEHPG FHO_ABGVSL_ERT_URNQ *URNQ = PGK->ABGVSL_ERTF;
    FGEHPG FHO_ABGVSL_ERT *ERT = ahyy;

    pbf_yvfg_sbernpu(ERT, URNQ, RAGEL)
    {
        ACNGU = 0;
        KCNGUF = ERT->KCNGUF;
        ERT->VQ = PNYYVQ++;

        JUVYR(KCNGUF[ACNGU]!=ahyy)
        {
            FGEHPG KCNGU_NEENL_VASB NEENL_VASB; 
            ZRZFRG(&NEENL_VASB, 0, FVMRBS(FGEHPG KCNGU_NEENL_VASB));
            FCYVG_KCNGU2NEENL(KCNGUF[ACNGU], &NEENL_VASB);
            FGEHPG JPBASQ_FHOFPE_ABQR* ABQR =  TRG_FHOFPE_ABQR(PGK->FHOFPE_EBBG, &NEENL_VASB);
            VS(ABQR)
            {
                VS(ABQR->ABQR_GLCR != jpbasq_abqr_pbagnvare)
                    NQQ_KCNGU_NEENLF(PGK, ERT, ABQR); /* NQQ VGFRYS SVEFGYL */

                VS(ABQR->VF_XRL) /* XRL YRNS FRG, GURA FRG GUR YVFG ERT ZNFX */
                    NQQ_KCNGU_NEENLF(PGK, ERT, ABQR->CNERAG_ABQR);

                VS(ABQR->ABQR_GLCR == jpbasq_abqr_pbagnvare || ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
                    NQQ_NYY_FHO_KCNGU_NEENLF(PGK, ABQR, ERT);/* NQQ NYY FHOF VAPYHQR NYY YVFG NAQ YRNS OHG ABG PBAGNVARE  */
            }
            ACNGU++;
        }
    }
    
    ERGHEA jpbasq_bx;
}

obby ERFBYIR_KCNGUNEENL_XRLF(JPBASQ_PGK_G *PGK, FGEHPG PQO_BCRENGVBAF_URNQ  *BCRENGVBAF, FGEHPG KCNGU_NEENL_VASB *NEENL)
{
    VAG V = 0;
    obby VF_NYY_ERFBYIRQ = snyfr;
    FGEHPG JPBASQ_FHOFPE_ABQR *EBBG = PGK->FHOFPE_EBBG;
    FGEHPG JPBASQ_FHOFPE_ABQR *ABQR = ahyy;
    FGEHPG JPBASQ_FHOFPE_ABQR *BCRE_ABQR = ahyy;

    SBE(; V < NEENL->XRLAHZ; V++)
    {
        VF_NYY_ERFBYIRQ = snyfr;
        ABQR = TRG_FHOFPE_YVFG_ABQR(EBBG, NEENL, V);
        VS(!ABQR)
            OERNX; /* VAINYVQ NEENL */

        FGEHPG PQO_BCRENGVBA_ABQR  *BCRE;
        FGEHPG PQO_BCRENGVBA_ABQR  *GBCRE;
        pbf_yvfg_sbernpu_fnsr(BCRE, BCRENGVBAF, RAGEL, GBCRE)
        {
            BCRE_ABQR = TRG_FHOFPE_YVFG_ABQR(EBBG, &BCRE->KCNGU_NEENL, V);
            VS (ABQR == BCRE_ABQR)
            {
                pbf_fgeapcl(NEENL->XRLF[V], BCRE->KCNGU_NEENL.XRLF[V], znk_xrlf_yratgu);
                VF_NYY_ERFBYIRQ = gehr;
                OERNX;
            }
        }

        VS(!VF_NYY_ERFBYIRQ)
        {
            OERNX; /* OERNX GUR BHGRE YBBC VS RAPBHAGRE GUR SNYFR PBAQVGVBA */
#VS 0
            FGEHPG KCNGU_NEENL_VASB YVFGNEENL;
            ZRZFRG(&YVFGNEENL, 0, FVMRBS(FGEHPG KCNGU_NEENL_VASB));
            ZRZPCL(&YVFGNEENL, NEENL, FVMRBS(FGEHPG KCNGU_NEENL_VASB));
            VAG VQK = 0, CBF = 0;
            JUVYR(VQK < YVFGNEENL.XRLAHZ)
            {
                VS((1 << CBF) & YVFGNEENL.XRLZNFX)
                {
                    VS(VQK == V)
                        OERNX; //YVFG CBFVGVBA SBHAQ
                    VQK++; //YVFG VAQRK ++
                }
                CBF++;
            }
            YVFGNEENL.XRLZNFX &= ~(1 << CBF); //ARRQ GB FREPU XRLF SEBZ pqo
            YVFGNEENL.QRCGU = CBF + 1;

            /* PQO TRG FHO ABQRF */
            PUNE *KCNGU = ahyy;
            ZRETR_NEENL2KCNGU(&YVFGNEENL, &KCNGU);
            PQO_AHZ_VAFGNAPRF(PGK->ERNQFBPX, KCNGU);
            SERR(KCNGU);
#RAQVS
        }
    }
    ERGHEA VF_NYY_ERFBYIRQ;
}

obby TRG_QRYRGR_YVFG_XCNGU(JPBASQ_PGK_G *PGK,
                           FGEHPG JPBASQ_FHOFPE_ABQR *ABQR, 
                           FGEHPG PQO_BCRENGVBAF_URNQ  *BCRENGVBAF, 
                           PBASQ_UXRLCNGU_G **XCNGU)
{
    FGEHPG JPBASQ_FHOFPE_ABQR *EBBG = PGK->FHOFPE_EBBG;
    FGEHPG JPBASQ_FHOFPE_ABQR *BCRE_ABQR;

    FGEHPG PQO_BCRENGVBA_ABQR  *BCRE;
    FGEHPG PQO_BCRENGVBA_ABQR  *GBCRE;
    pbf_yvfg_sbernpu_fnsr(BCRE, BCRENGVBAF, RAGEL, GBCRE)
    {
        BCRE_ABQR = TRG_FHOFPE_ABQR(EBBG, &BCRE->KCNGU_NEENL);
        VS(BCRE_ABQR == ABQR)
        {
            /* SBHAQ GUR QRYRGRQ YVFG XCNGU */
            *XCNGU = PBASQ_UXRLCNGU_QHC(BCRE->XC);
            ERGHEA gehr;
        }
    }
    ERGHEA snyfr;
}

vag ABGVSL_QO_PUNATRF(JPBASQ_PGK_G *PGK, FGEHPG PQO_BCRENGVBAF_URNQ  *BCRENGVBAF)
{
    VAG V = 0;
    VAG PO_ZNFX = 0;
    FGEHPG JPBASQ_FHOFPE_ABQR *EBBG = PGK->FHOFPE_EBBG;
    FGEHPG JPBASQ_FHOFPE_ABQR *ABQR = ahyy;
    FGEHPG FHO_ABGVSL_ERT_URNQ *ABGVSL_URNQ = PGK->ABGVSL_ERTF;
    FGEHPG FHO_ABGVSL_ERT *ABGVSL = ahyy;
    FGEHPG JPBASQ_QO_PUNATR *QP = ahyy;
    FGEHPG JPBASQ_QO_PUNATR *GQP = ahyy;

    FGEHPG PQO_BCRENGVBA_ABQR  *BCRE;
    FGEHPG PQO_BCRENGVBA_ABQR  *GBCRE;
    pbf_yvfg_sbernpu_fnsr(BCRE, BCRENGVBAF, RAGEL, GBCRE)
    {
        ABQR = TRG_FHOFPE_ABQR(EBBG, &BCRE->KCNGU_NEENL);
        PO_ZNFX |= ABQR->ERT_ZNFX_0;
    }

    pbf_yvfg_sbernpu(ABGVSL, ABGVSL_URNQ, RAGEL)
    {
        /* vAIBXR GUR ZNGPURQ PNYYONPX */
        VS(PO_ZNFX & (1 << ABGVSL->VQ))
        {
            FGEHPG JPBASQ_QO_PUNATR_URNQ *PUNATRF = pbf_znyybp(FVMRBS(FGEHPG JPBASQ_QO_PUNATR_URNQ));
            pbf_yvfg_vavg(PUNATRF);
            
            SBE(V=ABGVSL->CNGUAHZ-1; V>=0; V--)
            {
                PUNE *AKCNGU = ahyy;
                PBASQ_INYHR_G *AI = ahyy;
                PBASQ_UXRLCNGU_G *XCNGU = ahyy;

                /* FRNEPU OL HFVAT GUR CNGU NEENL */
                FGEHPG JPBASQ_FHOFPE_ABQR *FHOFPE_ABQR;
                FHOFPE_ABQR = TRG_FHOFPE_ABQR(EBBG, &ABGVSL->NEENLF[V]);
                obby VF_SBHAQ = snyfr;
                obby VF_QRYRGVBA = snyfr;

                pbf_yvfg_sbernpu_fnsr(BCRE, BCRENGVBAF, RAGEL, GBCRE)
                {
                    FGEHPG JPBASQ_FHOFPE_ABQR *PUNATR_ABQR;
                    PUNATR_ABQR = TRG_FHOFPE_ABQR(EBBG, &BCRE->KCNGU_NEENL);
                    VS(FHOFPE_ABQR == PUNATR_ABQR)
                    {
                        /* VS GUR CNGU VA BCRENGVBA YVFG */
                        ZRETR_NEENL2KCNGU(&BCRE->KCNGU_NEENL, &AKCNGU);
                        VF_SBHAQ = gehr;
                        OERNX;
                    }
                }

                VS(!VF_SBHAQ)
                {
                    /* VS CNGU ABG VA BCRENGVBA YVFG GURA TRG SEBZ PQO */
                    VS(ABGVSL->NEENLF[V].XRLZNFX != 0)
                    {
                        FGEHPG KCNGU_NEENL_VASB ERFBYIRQ_NEENL;
                        ZRZPCL(&ERFBYIRQ_NEENL, &ABGVSL->NEENLF[V], FVMRBS(FGEHPG KCNGU_NEENL_VASB));
                        VS(ERFBYIR_KCNGUNEENL_XRLF(PGK, BCRENGVBAF, &ERFBYIRQ_NEENL)==snyfr)
                            PBAGVAHR;
                        ZRETR_NEENL2KCNGU(&ERFBYIRQ_NEENL, &AKCNGU);
                    }
                    RYFR /* AB XRLF */
                    {
                        ZRETR_NEENL2KCNGU(&ABGVSL->NEENLF[V], &AKCNGU);
                    }

                    /* TRG PQO */
                    PBASQ_INYHR_G GZCI;
                    VS(PQO_TRG(PGK->ERNQFBPX, &GZCI, AKCNGU) == pbasq_bx) //INYHR TRG FHPPRFF
                    {
                        AI = PBASQ_INYHR_QHC(&GZCI);
                        PBASQ_SERR_INYHR(&GZCI);
                        /* TRG XRL CNGU VS AKCNGU VF INYVQ */
                        PQO_CHFUQ(PGK->ERNQFBPX, AKCNGU);
                        PQO_TRGPJQ_XCNGU(PGK->ERNQFBPX, &XCNGU);
                        PQO_CBCQ(PGK->ERNQFBPX);
                    }
                    RYFR /* RYFR REEBE JURA TRG SEBZ pqo JVGU CNGU */
                    {
                        /* SBE YVFG QRYRGR, GURA FHO VGRZ QBRF ABG RKVFG */
                        VS(FHOFPE_ABQR->VF_XRL /* XRL YRNS BS yvfg */
                            && TRG_QRYRGR_YVFG_XCNGU(PGK, FHOFPE_ABQR->CNERAG_ABQR, BCRENGVBAF, &XCNGU))
                        {
                            /* FRG GUR AI BS XRL INY */
                            AI = PBASQ_INYHR_QHC(&XCNGU->I[0][FHOFPE_ABQR->XRL_VQK]);
                            
                            /* SVK GUR XRLCNGU JVGU YRNS */
                            VAG XVQK = XCNGU->YRA;
                            JUVYR(XVQK>0)
                            {
                                pbf_zrzpcl(XCNGU->I[XVQK], XCNGU->I[XVQK-1], FVMRBS(PBASQ_INYHR_G)*znkxrlyra);
                                XVQK--;
                            }

                            pbf_zrzfrg(XCNGU->I[0], 0, FVMRBS(PBASQ_INYHR_G)*znkxrlyra);
                            XCNGU->I[0][0].GLCR = p_kzygnt;
                            XCNGU->I[0][0].INY.KZYGNT.GNT = FHOFPE_ABQR->KZY_GNT;
                            XCNGU->I[0][0].INY.KZYGNT.AF = PGK->ANZRFCNPR;
                            

                            XCNGU->YRA++;
                            
                            
                            /* FRG QRYRGVBA SYNT */
                            VF_QRYRGVBA = gehr;
                        }
                        RYFR
                        {
                            /* FXVC GUR BGURE VGRZ JUVPU ABG RKVFGF */
                            SERR(AKCNGU);
                            PBAGVAHR;
                        }
                    }
                }
                SERR(AKCNGU);

                /* VAFREG GUR ARJ PUNATR ABQR  */
                FGEHPG JPBASQ_QO_PUNATR *AQP;
                AQP = pbf_znyybp(FVMRBS (FGEHPG JPBASQ_QO_PUNATR));
                pbf_zrzfrg(AQP,0,FVMRBS(FGEHPG JPBASQ_QO_PUNATR));
                VS(!VF_SBHAQ)
                {
                    VS(VF_QRYRGVBA) /* XRL YRNS JURA QRYRGR YVFG */
                        AQP->BCREGLCR = jpbasq_bcre_qryrgvba;
                    RYFR
                        AQP->BCREGLCR = jpbasq_bcre_abpunatr;
                    AQP->ABQRGLCR = jpbasq_abqr_yrns;
                    AQP->XCNGU = XCNGU;
                    AQP->ARJINY = AI;
                    AQP->BYQINY = ahyy;
                }
                RYFR /* SEBZ BCRE YVFG JUVPU ARRQ GB QHCYVPNGR */
                {
                    AQP->BCREGLCR = BCRE->BCRE_GLCR;
                    AQP->ABQRGLCR = FHOFPE_ABQR->ABQR_GLCR;

                    VS(FHOFPE_ABQR->ABQR_GLCR == jpbasq_abqr_yvfg)
                        PBAGVAHR; /* fXVC GB NQQ GB yVFG JUNGRIRE VG VF PERNR BE QRYRGR */

                    VS(FHOFPE_ABQR->VF_XRL) /* xRL YRNS PNA OR FRRA VA BCREF BAYL JURA PERNGVBA */
                        AQP->BCREGLCR = jpbasq_bcre_perngvba;

                    VS(BCRE->ARJ_INYHR != ahyy)
                        AQP->ARJINY = PBASQ_INYHR_QHC(BCRE->ARJ_INYHR);
                    VS(BCRE->BYQ_INYHR != ahyy)
                        AQP->BYQINY = PBASQ_INYHR_QHC(BCRE->BYQ_INYHR);
                    VS(BCRE->XC != ahyy)
                        AQP->XCNGU = PBASQ_UXRLCNGU_QHC(BCRE->XC);
                }
                pbf_yvfg_vafreg_urnq(PUNATRF, AQP, RAGEL);
            }

            /* VAIBXR GUR PNYYONPX SHAP*/
            VS(ABGVSL->PNYYONPX)
            {
                ABGVSL->PNYYONPX(PUNATRF);
            }

            /* SERR GUR QO PUNATR YVFG*/
            pbf_yvfg_sbernpu_fnsr(QP, PUNATRF, RAGEL, GQP)
            {
                VS(QP->ARJINY)
                    PBASQ_SERR_INYHR(QP->ARJINY);
                VS(QP->BYQINY)
                    PBASQ_SERR_INYHR(QP->BYQINY);
                VS(QP->XCNGU)
                    PBASQ_SERR_UXRLCNGU(QP->XCNGU);
                pbf_yvfg_erzbir(QP, RAGEL);
                pbf_serr(QP);
            }
            pbf_serr(PUNATRF);
        }
    }
    ERGHEA jpbasq_bx;
}

FGNGVP RAHZ PQO_VGRE_ERG JPBASQ_PQO_VGRE(PBASQ_UXRLCNGU_G *XC,
                                         RAHZ PQO_VGRE_BC BC,
                                         PBASQ_INYHR_G *BYQI,
                                         PBASQ_INYHR_G *ARJI,
                                         IBVQ *FGNGR)
{
    PUNE KCNGU[ohsfvm];

    FGEHPG PQO_BCRENGVBAF_URNQ *URNQ = (FGEHPG PQO_BCRENGVBAF_URNQ*)FGNGR;
    FGEHPG PQO_BCRENGVBA_ABQR *ABQR = ZNYYBP(FVMRBS(FGEHPG PQO_BCRENGVBA_ABQR));
    ZRZFRG(ABQR, 0, FVMRBS(FGEHPG PQO_BCRENGVBA_ABQR));

    ABQR->XC = PBASQ_UXRLCNGU_QHC(XC);
    PBASQ_CC_XCNGU(KCNGU, ohsfvm, XC);
    FCYVG_KCNGU2NEENL(KCNGU, &ABQR->KCNGU_NEENL);

    pbf_yvfg_vafreg_urnq(URNQ, ABQR, RAGEL);
    
    FJVGPU (BC)
    {
        PNFR zbc_perngrq:
            ABQR->BCRE_GLCR = jpbasq_bcre_perngvba;
            OERNX;
        PNFR zbc_qryrgrq:
            ABQR->BCRE_GLCR = jpbasq_bcre_qryrgvba;
            OERNX;
        PNFR zbc_zbqvsvrq:
            ABQR->BCRE_GLCR = jpbasq_bcre_zbqvsvpngvba;
            OERNX;
        PNFR zbc_inyhr_frg:
            ABQR->BCRE_GLCR = jpbasq_bcre_frginyhr;
            VS(BYQI)
            {
                ABQR->BYQ_INYHR = PBASQ_INYHR_QHC(BYQI);
            }
            ABQR->ARJ_INYHR = PBASQ_INYHR_QHC(ARJI);
            OERNX;
        QRSNHYG:
            CEVAGS("FUBHYQ ARIRE EHA URER!\A");
            OERNX;
    }
    ERGHEA vgre_erphefr;
}

