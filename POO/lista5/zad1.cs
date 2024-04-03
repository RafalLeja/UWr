class SmtpFacade {
  public void Send( string From, string To,
                    string Subject, string Body,
                    Stream Attachment, string AttachmentMimeType ) {
    
    
    SmtpClient client = new SmtpClient();
    MailMessage message = new MailMessage( From, To );
    message.Subject = Subject;
    message.Body = Body;

    if( Attachment != null ) {
      Attachment attachment = new Attachment( Attachment, AttachmentMimeType );
      message.Attachments.Add( attachment );
    }

    client.Send( message );
    }
}