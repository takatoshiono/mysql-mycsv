/* Tell GCC  this is a header file */
#ifdef __GNUCC__
#pragma interface
#endif

/* The CSV lines could be big. Read them in blocks of 512. */
#define CSV_READ_BLOCK_SIZE   512

/* 
  Following the tradition of other storage engines, we put all of the 
  low-level information under a separate structure.
 */ 
struct CSV_INFO
{
  char fname[FN_REFLEN+1];
  int fd;
} ;

void dump_explain();

/* Now define the handler class. */
class ha_csv: public handler
{
protected:
  /* Low-level storage engine data. */
  CSV_INFO* file;
  
  /* Lock structures for the table lock manager. */
  THR_LOCK_DATA lock;
  THR_LOCK thr_lock;
  
  /* Table scan cursor.*/
  my_off_t pos;
  
  /* Buffer for reading CSV line blocks. */
  char read_buf[CSV_READ_BLOCK_SIZE];
  
  /* Buffer for parsing the field values. */
  String field_buf;
  
  /* See the comment in the implementation file. */
  int fetch_line(byte* buf);
  
  /* Initializes the storage engine object for a sequential scan. */
  int rnd_init(bool scan) 
  {
    pos = 0; 
    records = 0;
    dump_explain();
    return 0;
  }
  int index_init(uint idx)
  {
    active_index=idx;
    dump_explain();
    return 0;
  }
public:
 /* Constructor. */
 ha_csv(TABLE* table): handler(table), file(0) {}
 
 /* Destructor. */
 ~ha_csv() {}
 
 /* See the comments in the implementation file for the methods below. */
 int open(const char *name, int mode, uint test_if_locked);
 int close(void);
 int rnd_next(byte *buf);
 int rnd_pos(byte * buf, byte *pos);
 void position(const byte *record);
 void info(uint flags);
 int external_lock(THD *thd, int lock_type);
 const char **bas_ext() const;
 ulong table_flags(void) const;
 ulong index_flags(uint idx, uint part, bool all_parts) const;
 int create(const char *name, TABLE *form, HA_CREATE_INFO *info);
 THR_LOCK_DATA **store_lock(THD *thd,
				     THR_LOCK_DATA **to,
				     enum thr_lock_type lock_type);
 
 /* 
   Returns the storage engine type string used in the output of
   SHOW TABLE STATUS
 */                          
 const char *table_type() const { return "OREILLY_CSV"; } 
  
};
