/* WashingMashine
 * Author: ElizaLo
 * Creation date: 5/10/19
 */
 
MACHINE
    WashingMashine    
SETS
    WASHING_MACHINE = {WORKING, PAUSE, ALERT};
    ELECTRICITY = {ELEC_YES, ELEC_NONE};
    WATER = {WATER_YES, WATER_NONE};
    SOAP_POWDER = {S_P_YES, S_P_NONE};
    CONDITIONER = {COND_YES, COND_NONE};
    SOAP_POWDER_WATER = {SPW_YES, SPW_NONE};
    DOORS = {OPENED, CLOSED};
    PROGRAMME = {PROGPAMME_YES, PROGPAMME_NONE};
    OPTIONS = {OP_NONE, TEMP_YES, TEMP_NONE, BLUR, RINSE, RINSE_WITH_COND, PRESS_UP};
    LAUNDER = {LAUNDER_DONE, ERROR}

VARIABLES
    Washing_Machine,
    Electricity,
    Water,
    Soap_Powder,
    Conditioner,
    Soap_Powder_Water, 
    Doors,
    Programme,
    Options,
    Launder
    
INVARIANT
    Washing_Machine : WASHING_MACHINE &
    Electricity : ELECTRICITY &
    Water : WATER &
    Soap_Powder : SOAP_POWDER &
    Conditioner : CONDITIONER &
    Soap_Powder_Water : SOAP_POWDER_WATER &
    Doors : DOORS &
    Programme : PROGRAMME &
    Options : OPTIONS &
    Launder : LAUNDER &
    
    ((Electricity = ELEC_NONE) => (Washing_Machine = ALERT)) &
    ((Water = WATER_NONE) => (Washing_Machine = ALERT)) &
    ((Soap_Powder = S_P_NONE) => (Washing_Machine = ALERT)) &
    ((Programme = PROGPAMME_NONE) => (Washing_Machine = ALERT)) &
    ((Options = RINSE & Conditioner = COND_NONE & Water = WATER_YES) => (Washing_Machine = ALERT)) &
    ((Doors = OPENED) => (Washing_Machine = ALERT)) &
    ((Options = RINSE & Conditioner = COND_YES & Water = WATER_NONE) => (Washing_Machine = ALERT)) &
    ((Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
            Programme = PROGPAMME_YES) => (Launder = LAUNDER_DONE)) &
    ((Washing_Machine = WORKING & Options = RINSE & Electricity = ELEC_YES & Water = WATER_YES & Conditioner = COND_YES &
            Programme = PROGPAMME_YES & Soap_Powder = S_P_YES) => (Launder = LAUNDER_DONE)) &
    ((Washing_Machine = WORKING & Electricity = ELEC_NONE & Water = WATER_YES & Soap_Powder = S_P_YES &
        Programme = PROGPAMME_YES) => (Launder = ERROR)) &
    ((Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_NONE & Soap_Powder = S_P_YES &
        Programme = PROGPAMME_YES) => (Launder = ERROR)) 
    
INITIALISATION
    Washing_Machine := WORKING ||
    Electricity := ELEC_YES ||
    Water := WATER_YES ||
    Soap_Powder := S_P_YES ||
    Conditioner := COND_YES ||
    Soap_Powder_Water := SPW_YES || 
    Doors := CLOSED ||
    Programme := PROGPAMME_YES ||
    Options := OP_NONE ||
    Launder := LAUNDER_DONE 

OPERATIONS
    autAlertElectricity =
    PRE Electricity = ELEC_NONE
    THEN
             Washing_Machine := ALERT
    END;
    
    autAlertWater =
    PRE Water = WATER_NONE
    THEN
        Washing_Machine := ALERT
    END;

    autAlertSoapPowder =
    PRE Soap_Powder = S_P_NONE
    THEN
        Washing_Machine := ALERT
    END;
    
    autAlertDoors =
    PRE Doors = OPENED
    THEN
        Washing_Machine := ALERT
    END;
    
    autAlertProgramme =
    PRE Programme = PROGPAMME_NONE
    THEN
        Washing_Machine := ALERT
    END;
    
    washingNormal =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED
    THEN
        Launder := LAUNDER_DONE
    END;
    
    washingNormalError_1 =
    PRE Washing_Machine = WORKING & Electricity = ELEC_NONE & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED
    THEN
        Launder := ERROR
    END;
    
    washingNormalError_2 =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_NONE & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED
    THEN
        Launder := ERROR
    END;
    
    washingNormalError_3 =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_NONE & Soap_Powder = S_P_NONE & 
        Programme = PROGPAMME_YES & Doors = CLOSED
    THEN
        Launder := ERROR
    END;
    
    washingNormalError_4 =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_NONE & Doors = CLOSED
    THEN
        Launder := ERROR
    END;
    
    washingNormalError_5 =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = OPENED
    THEN
        Launder := ERROR
    END;
    
    washingWithCond =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED & Options = RINSE_WITH_COND & Conditioner = COND_YES
    THEN
        Launder := LAUNDER_DONE
    END;
    
    washingWithCondError_1 =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED & Options = RINSE_WITH_COND & Conditioner = COND_NONE
    THEN
        Launder := ERROR
    END;
    
    washingWithCondError =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_NONE & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED & Options = RINSE_WITH_COND & Conditioner = COND_YES
    THEN
        Launder := ERROR
    END;
    
    washingWithPressUp =
    PRE Washing_Machine = WORKING & Electricity = ELEC_YES & Water = WATER_YES & Soap_Powder = S_P_YES & 
        Programme = PROGPAMME_YES & Doors = CLOSED & Options = PRESS_UP
    THEN
        Launder := LAUNDER_DONE
    END   
END