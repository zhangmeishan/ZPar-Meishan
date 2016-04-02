// Copyright (C) University of Oxford 2010
/****************************************************************
 *                                                              * 
* xxxx.h - the penn treebank style dependency labels           * 
*                                                              * 
* Author: xxx  xxxx                                            * 
 *                                                              * 
* Computing Laboratory, Oxford. 2008.07                        * 
 *                                                              * 
 ****************************************************************/
const std::string PENN_DEP_STRINGS[] = {
        "-NONE-",
        "ROOT",
        "AMOD",
        "DEP",
        "NMOD",
        "OBJ",
        "P",
        "PMOD",
        "PRD",
        "SBAR",
        "SUB",
        "VC",
        "VMOD",
        "root",
        "locationfin",
        "locationini",
        "locationthru",
        "ofpart",
        "pu",
        "statefin",
        "stateini",
        "timeadv",
        "timefin",
        "timeini",
        "accompaniment",
        "agent",
        "angle",
        "aspect",
        "aux-depend",
        "basis",
        "beneficiary",
        "c-agent",
        "c-basis",
        "c-content",
        "c-patient",
        "cause",
        "causer",
        "comment",
        "concerning",
        "content",
        "contrast",
        "cost",
        "d-locphrase",
        "d-timephrase",
        "d-attribute",
        "d-category",
        "d-content",
        "d-deno",
        "d-deno-p",
        "d-domain",
        "d-genetive",
        "d-host",
        "d-material",
        "d-member",
        "d-quantity",
        "d-quantity-p",
        "d-restrictive",
        "d-sequence",
        "d-sequence-p",
        "degree",
        "direction",
        "distance",
        "duration",
        "emphasis",
        "existent",
        "experiencer",
        "frequency",
        "instrument",
        "isa",
        "j-agent",
        "j-content",
        "j-existent",
        "j-experiencer",
        "j-instrument",
        "j-isa",
        "j-location",
        "j-means",
        "j-partner",
        "j-patient",
        "j-possession",
        "j-possessor",
        "j-relevant",
        "location",
        "manner",
        "material",
        "means",
        "modal",
        "negation",
        "partner",
        "patient",
        "possession",
        "possessor",
        "prep-depend",
        "qp-mod",
        "r-agent",
        "r-basis",
        "r-causer",
        "r-content",
        "r-existent",
        "r-experiencer",
        "r-instrument",
        "r-location",
        "r-means",
        "r-partner",
        "r-patient",
        "r-possession",
        "r-possessor",
        "r-relevant",
        "r-state",
        "r-whole",
        "relevant",
        "s-abandonment",
        "s-besides",
        "s-cause",
        "s-concerning",
        "s-concession",
        "s-condition",
        "s-coordinate",
        "s-measure",
        "s-or",
        "s-preference",
        "s-progression",
        "s-purpose",
        "s-recount",
        "s-result",
        "s-succession",
        "s-summary",
        "scope",
        "sequence",
        "sequence-p",
        "state",
        "succeeding",
        "time",
        "times",
        "whole",
};


enum PENN_DEP_LABELS {
    PENN_DEP_NONE=0,
    PENN_DEP_ROOT,
    PENN_DEP_AMOD,
    PENN_DEP_DEP,
    PENN_DEP_NMOD,
    PENN_DEP_OBJ,
    PENN_DEP_P,
    PENN_DEP_PMOD,
    PENN_DEP_PRD,
    PENN_DEP_SBAR,
    PENN_DEP_SUB,
    PENN_DEP_VC,
    PENN_DEP_VMOD,
    PENN_HIT_ROOT,
    PENN_HIT_LocationFin,
    PENN_HIT_LocationIni,
    PENN_HIT_LocationThru,
    PENN_HIT_OfPart,
    PENN_HIT_PU,
    PENN_HIT_StateFin,
    PENN_HIT_StateIni,
    PENN_HIT_TimeAdv,
    PENN_HIT_TimeFin,
    PENN_HIT_TimeIni,
    PENN_HIT_accompaniment,
    PENN_HIT_agent,
    PENN_HIT_angle,
    PENN_HIT_aspect,
    PENN_HIT_aux_depend,
    PENN_HIT_basis,
    PENN_HIT_beneficiary,
    PENN_HIT_c_agent,
    PENN_HIT_c_basis,
    PENN_HIT_c_content,
    PENN_HIT_c_patient,
    PENN_HIT_cause,
    PENN_HIT_causer,
    PENN_HIT_comment,
    PENN_HIT_concerning,
    PENN_HIT_content,
    PENN_HIT_contrast,
    PENN_HIT_cost,
    PENN_HIT_d_LocPhrase,
    PENN_HIT_d_TimePhrase,
    PENN_HIT_d_attribute,
    PENN_HIT_d_category,
    PENN_HIT_d_content,
    PENN_HIT_d_deno,
    PENN_HIT_d_deno_p,
    PENN_HIT_d_domain,
    PENN_HIT_d_genetive,
    PENN_HIT_d_host,
    PENN_HIT_d_material,
    PENN_HIT_d_member,
    PENN_HIT_d_quantity,
    PENN_HIT_d_quantity_p,
    PENN_HIT_d_restrictive,
    PENN_HIT_d_sequence,
    PENN_HIT_d_sequence_p,
    PENN_HIT_degree,
    PENN_HIT_direction,
    PENN_HIT_distance,
    PENN_HIT_duration,
    PENN_HIT_emphasis,
    PENN_HIT_existent,
    PENN_HIT_experiencer,
    PENN_HIT_frequency,
    PENN_HIT_instrument,
    PENN_HIT_isa,
    PENN_HIT_j_agent,
    PENN_HIT_j_content,
    PENN_HIT_j_existent,
    PENN_HIT_j_experiencer,
    PENN_HIT_j_instrument,
    PENN_HIT_j_isa,
    PENN_HIT_j_location,
    PENN_HIT_j_means,
    PENN_HIT_j_partner,
    PENN_HIT_j_patient,
    PENN_HIT_j_possession,
    PENN_HIT_j_possessor,
    PENN_HIT_j_relevant,
    PENN_HIT_location,
    PENN_HIT_manner,
    PENN_HIT_material,
    PENN_HIT_means,
    PENN_HIT_modal,
    PENN_HIT_negation,
    PENN_HIT_partner,
    PENN_HIT_patient,
    PENN_HIT_possession,
    PENN_HIT_possessor,
    PENN_HIT_prep_depend,
    PENN_HIT_qp_mod,
    PENN_HIT_r_agent,
    PENN_HIT_r_basis,
    PENN_HIT_r_causer,
    PENN_HIT_r_content,
    PENN_HIT_r_existent,
    PENN_HIT_r_experiencer,
    PENN_HIT_r_instrument,
    PENN_HIT_r_location,
    PENN_HIT_r_means,
    PENN_HIT_r_partner,
    PENN_HIT_r_patient,
    PENN_HIT_r_possession,
    PENN_HIT_r_possessor,
    PENN_HIT_r_relevant,
    PENN_HIT_r_state,
    PENN_HIT_r_whole,
    PENN_HIT_relevant,
    PENN_HIT_s_abandonment,
    PENN_HIT_s_besides,
    PENN_HIT_s_cause,
    PENN_HIT_s_concerning,
    PENN_HIT_s_concession,
    PENN_HIT_s_condition,
    PENN_HIT_s_coordinate,
    PENN_HIT_s_measure,
    PENN_HIT_s_or,
    PENN_HIT_s_preference,
    PENN_HIT_s_progression,
    PENN_HIT_s_purpose,
    PENN_HIT_s_recount,
    PENN_HIT_s_result,
    PENN_HIT_s_succession,
    PENN_HIT_s_summary,
    PENN_HIT_scope,
    PENN_HIT_sequence,
    PENN_HIT_sequence_p,
    PENN_HIT_state,
    PENN_HIT_succeeding,
    PENN_HIT_time,
    PENN_HIT_times,
    PENN_HIT_whole,
   PENN_DEP_COUNT
};


const unsigned long PENN_DEP_COUNT_BITS = 8;

/*==============================================================
 *
 * dependency lab
 *
 *==============================================================*/

class CDependencyLabel {

public:

   enum {NONE=0};
   enum {ROOT0=PENN_DEP_ROOT};
   enum {ROOT1=PENN_HIT_ROOT};
   enum {FIRST=ROOT0};
   enum {COUNT=PENN_DEP_COUNT};
   enum {MAX_COUNT=COUNT};
   enum {SIZE=PENN_DEP_COUNT_BITS};

protected:

   unsigned long m_code;

public:

   CDependencyLabel() : m_code(NONE) {}
   CDependencyLabel(const unsigned long &code) : m_code(code) { }
   CDependencyLabel(const std::string &str) { load(str); }
   virtual ~CDependencyLabel() {}

public:

   const unsigned long &hash() const { return m_code; }
   bool operator == (const CDependencyLabel &l) const { return m_code == l.m_code; }
   bool operator != (const CDependencyLabel &l) const { return m_code != l.m_code; }
   bool operator < (const CDependencyLabel &l) const { return m_code < l.m_code; }
   bool operator > (const CDependencyLabel &l) const { return m_code > l.m_code; }
   bool operator <= (const CDependencyLabel &l) const { return m_code <= l.m_code; }
   bool operator >= (const CDependencyLabel &l) const { return m_code >= l.m_code; }

   void load(const std::string &str) { 
      m_code = PENN_DEP_NONE;
      for (int i=FIRST; i<COUNT; ++i) {
         if (PENN_DEP_STRINGS[i]==str) {
            m_code = i;
            return;
         }
      }
   }

   void load(const unsigned long &u) { 
      m_code = u;
   }

   const std::string &str() const { 
      return PENN_DEP_STRINGS[ m_code ]; 
   }

   const unsigned long &code() const {
      return m_code;
   }

};

inline std::istream & operator >> (std::istream &is, CDependencyLabel &label) {
   std::string s;
   is >> s;
   label.load(s);
   return is;
}

inline std::ostream & operator << (std::ostream &os, const CDependencyLabel &label) {
   os << label.str() ;
   return os;
}
