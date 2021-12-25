namespace TimeServer
{
    partial class Form1
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다.
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마십시오.
        /// </summary>
        private void InitializeComponent()
        {
            this._btnServerStart = new System.Windows.Forms.Button();
            this._btnServerEnd = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // _btnServerStart
            // 
            this._btnServerStart.AccessibleName = "Start";
            this._btnServerStart.Font = new System.Drawing.Font("Monaco", 9F);
            this._btnServerStart.Location = new System.Drawing.Point(120, 30);
            this._btnServerStart.Name = "_btnServerStart";
            this._btnServerStart.Size = new System.Drawing.Size(240, 60);
            this._btnServerStart.TabIndex = 0;
            this._btnServerStart.Text = "단일 서버 시작";
            this._btnServerStart.UseVisualStyleBackColor = true;
            // 
            // _btnServerEnd
            // 
            this._btnServerEnd.AccessibleName = "End";
            this._btnServerEnd.Font = new System.Drawing.Font("Monaco", 9F);
            this._btnServerEnd.Location = new System.Drawing.Point(120, 113);
            this._btnServerEnd.Name = "_btnServerEnd";
            this._btnServerEnd.Size = new System.Drawing.Size(240, 60);
            this._btnServerEnd.TabIndex = 1;
            this._btnServerEnd.Text = "단일 서버 종료";
            this._btnServerEnd.UseVisualStyleBackColor = true;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(464, 211);
            this.Controls.Add(this._btnServerEnd);
            this.Controls.Add(this._btnServerStart);
            this.Name = "Form1";
            this.Text = "Form1";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button _btnServerStart;
        private System.Windows.Forms.Button _btnServerEnd;
    }
}

