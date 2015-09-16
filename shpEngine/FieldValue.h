
#ifndef FieldValue_h
#define FieldValue_h 

//	《说明》：一个字段的值
class FieldValue 
{

  public:
      FieldValue();

      ~FieldValue();


      int GetInt ();
      void SetInt (int value);
      double GetDouble ();
      void SetDouble (double value);
      const char* GetString ();
      void SetString (const char* value);

  private:
      char* m_pValue;
};
#endif
